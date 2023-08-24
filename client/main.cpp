#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <string.h>

#include <vector>
#include <iostream>
#include <thread>

#ifdef __WIN32__
# include <winsock2.h>
#else
# include <arpa/inet.h>
# include <sys/socket.h>
#endif
using namespace std;

/* options */
bool search = false;
char searchstr[35];
bool target = false;
char targethash[512];

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
    return -1;
  }
#endif
  for (int loop=0;loop<argc;loop++) {
    if (strcmp(argv[loop], "-h")==0 | strcmp(argv[loop], "-help")==0) {
      printf("\ncrappytorrent 0 client\n-s <name> search for\n-d <hash> download from hash\n-t <protocol://address:port> add a tracker\n\n");
    }
    if (strcmp(argv[loop], "-s")==0) {
      loop++;
      if (argv[loop]==NULL) {
        printf("Bad argument \"-s\"");
        return -2;
      }
      search = true;
      memcpy(searchstr,argv[loop],35);
    }
    if (strcmp(argv[loop], "-d")==0) {
      loop++;
      if (argv[loop]==NULL) {
        printf("Bad argument \"-d\"");
        return -2;
      }
      target = true;
      memcpy(targethash,argv[loop],512);
    }
  }
  printf("%s-",searchstr);
#ifdef _WIN32
  WSACleanup();
#endif
  return 0;
}