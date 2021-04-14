from stem.control import Controller
import stem
import stem.process
import getpass
import subprocess
from os import system
from stem.util import term
import os
def print_bootstrap_lines(line):
  if "Bootstrapped " in line:
    print(term.format(line, term.Color.BLUE))

# tor_p = stem.process.launch_tor(init_msg_handler = print_bootstrap_lines)
print("hell")
tor_p = stem.process.launch_tor(init_msg_handler = print_bootstrap_lines, torrc_path="./VM3")
tor_p.kill()