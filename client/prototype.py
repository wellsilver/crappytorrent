# protocol prototyper (why is python so easy to use lol)
# 
# 
# 
# 

"""

"""

from socket import *

def server():
  s = socket(AF_INET, SOCK_DGRAM)
  dat:bytes = bytes("e")
  while True:
    dat, fro = s.recvfrom()
    if dat.startswith((1).to_bytes(length=1,byteorder='little')): # do u hav?
      pass
    if dat.startswith((2).to_bytes(length=1,byteorder='little')): # can u send this data plz
      pass
    if dat.startswith((3).to_bytes(length=1,byteorder='little')): # please search ur indexes for this thing, tell me if u know where it is thx
      pass

server()