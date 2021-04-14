# https://stem.torproject.org/tutorials/to_russia_with_love.html
# https://stackoverflow.com/questions/2473655/how-to-make-a-call-to-an-executable-from-python-script
from stem.control import Controller
import stem
import stem.process
import getpass
import subprocess
from os import system
from stem.util import term
import os
FILEPATH = "/tmp/relay_fingerprints.txt"
PROG = "gedit"
#https://metrics.torproject.org/rs.html#toprelays
EXIT_FINGERPRINT = '18EAE30A4585BEB0D63D36BCFE3F9CA786CB55C7'

def clear():
	clear = lambda: system('clear')

# from https://stem.torproject.org/tutorials/to_russia_with_love.html
def print_bootstrap_lines(line):
  if "Bootstrapped " in line:
    print(term.format(line, term.Color.BLUE))


if __name__ == '__main__':
	tor_p = stem.process.launch_tor(init_msg_handler = print_bootstrap_lines, torrc_path="/etc/tor/torrc")
	try: 
		with Controller.from_port() as controller:
			auth_err=0
			try:
				print("pass: tor")
				ps=getpass.getpass("Controller password: ")
				controller.authenticate(password=ps)
			except:
				print("Cannot authenticate controller!")
				auth_err=1
			
			if not auth_err:

				# print("Tor is running version %s" % controller.get_version())

				# bytes_read = int(controller.get_info("traffic/read"))
				# bytes_written = int(controller.get_info("traffic/written"))

				# print("My Tor relay has read %s Mbytes and written %s." % (str(bytes_read/((1024**2))), str(bytes_written/(1024**2))))

				print("::Creating temp file")
				try:
					f = open(FILEPATH, "w")
				except:
					print("ERROR::cannot create file")

				print("::Writing relay fingerprints")
				try:
					relay_fingerprints = [desc.fingerprint for desc in controller.get_network_statuses()]
				except:
					print("ERROR::cannot get network statuses, check internet")

				for fingerprints in relay_fingerprints:
					f.write(fingerprints)
					f.write("\n")
				f.close()

				args= (PROG , FILEPATH)
				popen = subprocess.Popen(args, stdout=subprocess.PIPE)

				clear()
				length=int(input("Enter relay size(exluding the exit point: ")) 
				stream=[]
				for _r in range(length):
					_s=input("relay "+str(_r+1)+":")
					stream.append(_s)
				stream.append(EXIT_FINGERPRINT)

				print("::Creating circuit")

				circuit_id = controller.new_circuit(stream, await_build = True)

				input("press enter to exit...")
				print("::Deleting temp fingerprint file")
				os.remove(FILEPATH)

				ch=input("Do you want to kill tor? (y/n)")
				if(ch=='y' or ch=='Y'):
					print("::Killing tor")
					args= ("systemctl" , "stop", "tor")
					popen = subprocess.Popen(args, stdout=subprocess.PIPE)

	except stem.SocketError as er:
		print("Error: ", er, "\nTry starting tor service.")

	# finally:
		# tor_p.kill()