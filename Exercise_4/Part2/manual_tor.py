# https://stem.torproject.org/tutorials/to_russia_with_love.html
# https://stackoverflow.com/questions/2473655/how-to-make-a-call-to-an-executable-from-python-script
from stem.control import Controller
import stem
import stem.process
import getpass
from stem.util import term
import subprocess
from os import system
import os
FILEPATH = "/tmp/relay_fingerprints.txt"
PROG = "gedit"
#https://metrics.torproject.org/rs.html#toprelays
EXIT_FINGERPRINT = '18EAE30A4585BEB0D63D36BCFE3F9CA786CB55C7'
def print_bootstrap_lines(line):
  if "Bootstrapped " in line:
    print(term.format(line, term.Color.BLUE))

if __name__ == '__main__':
	tor_p = stem.process.launch_tor(init_msg_handler = print_bootstrap_lines, torrc_path="./VM1/VM1")

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

				length=int(input("Enter relay size:")) 
				stream=[]
				for _r in range(length):
					_s=input("relay "+str(_r+1)+":")
					stream.append(_s)

				print("::Creating circuit")

				circuit_id = controller.new_circuit(stream, await_build = True)

				input("press enter to exit...")
				
				# ch=input("Do you want to kill tor? (y/n)")
				# if(ch=='y' or ch=='Y'):
				# 	print("::Killing tor")
				# 	args= ("systemctl" , "stop", "tor")
				# 	popen = subprocess.Popen(args, stdout=subprocess.PIPE)
	except stem.SocketError as er:
		print("Error: ", er, "\nTry starting tor service.")
	finally:
		tor_p.kill()