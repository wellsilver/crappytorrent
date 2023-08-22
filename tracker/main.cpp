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
uint16_t port = 4079; // -p <port>
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

int fd;

// thread th(server);
void server() {
  int opt = 1;
  struct sockaddr_in address;
  int rslt;

  fd = socket(AF_INET, SOCK_DGRAM, 0);
  
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

  rslt = bind(fd, (struct sockaddr*)&address, sizeof(address));

  if (rslt == -1) {
    printf("- could not bind to  %i\n", port);
    close(fd);
    return;
  }

  close(fd);
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
      printf("\ncrappytorrent 0\n-s run only as server\n-p <port> choose custom port for peer sharing\n-H <ipv4> choose the host\n\n");
    }
    if (strcmp(argv[loop],"-s") == 0) { // if -s option sent
      isserver = true;
    }
    if (strcmp(argv[loop],"-p") == 0) {
      loop++;
      port = atoi(argv[loop]);
      
      if (port==0) {
        printf("Bad argument for \"-p\"");
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