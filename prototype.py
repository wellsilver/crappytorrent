# protocol prototyper (why is python so easy to use lol)
# 
# 
# 
# 

"""

"""

from socket import *
import sys

try:
  f = open("trackers.txt", "r")
except FileNotFoundError:
  f = open("trackers.txt", "w")

def server():
  s = socket(AF_INET6, SOCK_DGRAM)
  s.bind(("0:0:0:0:0:0:0:1", 4078))
  dat:bytes = bytes("e",encoding="utf-8")

  while True:
    dat, fro = s.recvfrom(300)
    to = socket(AF_INET6, SOCK_DGRAM)
    to.connect((fro[0], 4079))

    if dat.startswith(bytes('c')): # do u hav?
      pass
    if dat.startswith(bytes('r')): # can u send this data plz
      pass
    if dat.startswith(bytes('s')): # please search ur indexes for this thing, tell me if u know where it is thx
      to.sendb(bytes( [0] ))
    
    to.close()

if "-s" in sys.argv:
  server()