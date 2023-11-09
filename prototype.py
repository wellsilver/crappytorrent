# protocol prototyper (why is python so easy to use lol)
# 
# 
# 
# 


from socket import *
import sys

# peers.txt
# ipv6,port,firstseen,lastseen\n
# continues lol

# torrents.txt
# name,hash,"fileloc"

def getpeers() -> type(open()):
  try:
    f = open("peers.txt", "r+")
  except FileNotFoundError:
    f = open("peers.txt", "w+")
    f.close()
    f = open("peers.txt", "r+")
  return f

def gettorrents() -> type(open()):
  try:
    f = open("torrents.txt", "r+")
  except FileNotFoundError:
    f = open("torrents.txt", "w+")
    f.close()
    f = open("torrents.txt", "r+")
  return f

def server():
  com = socket(AF_INET, SOCK_DGRAM)
  com.bind(("localhost", 4533)) # com is for internal communication
  com.setblocking(False)

  s = socket(AF_INET6, SOCK_DGRAM)
  s.bind(("0:0:0:0:0:0:0:1", 4078))
  dat:bytes = bytes("e",encoding="utf-8")

  while True:
    dat, fro = s.recvfrom(300)
    to = socket(AF_INET6, SOCK_DGRAM)

    if dat.startswith(bytes('c')): # can u send me data about this data plz
      to.connect((fro[0], 4079))
      pass
    if dat.startswith(bytes('r')): # can u send this data plz
      to.connect((fro[0], 4079))
      pass
    if dat.startswith(bytes('s')): # please search ur indexes for this thing, tell me if u know where it is thx
      to.connect((fro[0], 4079))
      to.sendb(bytes(0))
    
    to.close()

if "-s" in sys.argv or "--server" in sys.argv:
  server()

for i in range(len(sys.argv)):
  print(i)