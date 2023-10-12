# protocol prototyper (why is python so easy to use lol)
# 
# 
# 
# 

"""
// a info packet type1
struct ackpacket {
  char type;
  int64_t ip;

  char data[1000];
} __attribute__((__packed__));

// a download packet type2
struct downpacket {
  char type;
  int64_t ip;

  char data[1000];
} __attribute__((__packed__));

// a search packet type3
struct searchpacket {
  char type;
  int64_t ip;

  char data[1000];
} __attribute__((__packed__));
"""

from socket import *

s = socket(AF_INET, SOCK_DGRAM)
dat:bytes = bytes("e")
while True:
  dat, fro = s.recvfrom()
  