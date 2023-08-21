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
bool isserver = false; // -s
uint16_t peerport = 4079; // -pp <port>
uint16_t downport = 4078; // -dp <port>
uint64_t host = 0; // -H <domain>

// a info packet type1
struct ackpacket {
  char type;
  int64_t ip;

  char data[1000];
} __attribute__((__packed__));

// a download packet type2
struct downpacket {
  char type;
  uint64_t sector;

  char data[1000];
} __attribute__((__packed__));

// a search packet type3
struct searchpacket {
  char type;
  int64_t ip;

  char data[1000];
} __attribute__((__packed__));

int dfd;
int pfd;
// thread th(server);
void server() {
  int opt = 1;
  struct sockaddr_in address;
  int rslt;

  pfd = socket(AF_INET, SOCK_DGRAM, 0);
  
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(peerport);

  rslt = bind(pfd, (struct sockaddr*)&address, sizeof(address));

  if (rslt == -1) {
    printf("- could not bind %i\n", peerport);
    close(pfd);
    return;
  }

  dfd = socket(AF_INET, SOCK_DGRAM, 0);

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(peerport);

  rslt = bind(dfd, (struct sockaddr*)&address, sizeof(address));

  if (rslt == -1) {
    printf("- could not bind %i\n", downport);
    close(dfd);
    return;
  }

  close(dfd);
  close(pfd);
}

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
      printf("\ncrappytorrent 0\n-s run only as server\n-pp <port> choose custom port for peer sharing\n-dp <port. choose custom port for peer downloading\n-H <ipv4> choose the host name\n\n");
    }
    if (strcmp(argv[loop],"-s") == 0) { // if -s option sent
      isserver = true;
    }
    if (strcmp(argv[loop],"-pp") == 0) {
      loop++;
      peerport = atoi(argv[loop]);
      
      if (peerport==0) {
        printf("Bad argument for \"-pp\"");
        return -1;
      }
    }
    if (strcmp(argv[loop],"-dp") == 0) {
      loop++;
      downport = atoi(argv[loop]);
      
      if (downport==0) {
        printf("Bad argument for \"-dp\"");
        return -1;
      }
    }
    if (strcmp(argv[loop], "-H") == 0) {
      loop++;
      host = inet_addr(argv[loop]);

      if (host==INADDR_NONE) {
        printf("Bad argument for \"-H\"");
        return -2;
      }
    }
  }

#ifdef _WIN32
  WSACleanup();
#endif
  return 0;
}