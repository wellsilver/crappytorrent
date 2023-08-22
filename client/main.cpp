#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#ifdef __WIN32__
# include <winsock2.h>
#else
# include <arpa/inet.h>
# include <sys/socket.h>
#endif
using namespace std;

/* options */
bool search;

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

int main(int argc, char **argv) {
#ifdef _WIN32
  WSADATA wsa;
  if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
    printf("Failed to initialize Winsock\n");
    return 1;
  }
#endif
  for (int loop=0;loop<argc;loop++) {
    if (strcmp(argv[loop], "-h")==0 | strcmp(argv[loop], "-help")==0) {
      printf("\ncrappytorrent 0 client\n-s <name> search for\n-d <hash> download from hash\n-t <protocol://address:port> add a tracker\n\n");
    }

  }

#ifdef _WIN32
  WSACleanup();
#endif
  return 0;
}