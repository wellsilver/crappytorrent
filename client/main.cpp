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

// a info packet
struct ackpacket {
  char type;
  int64_t ip;

  char blank[100];
} __attribute__((__packed__));

// a download packet
struct downpacket {
  char data[2000];
} __attribute__((__packed__));

// a search packet {
struct searchpacket {
  char type;
  int64_t ip;

  char string[100]; // what to search for
} __attribute__((__packed__));

int fd;
// thread th(server);
void server() {
  int opt = 1;
  int rslt;

  fd = socket(AF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(4080);

  rslt = bind(fd, (struct sockaddr*)&address, sizeof(address));

  if (rslt == -1) {
    printf("- server could not bind %i\n", errno);
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
    if (strcmp(argv[loop],"-s") == 0) { // if -s option sent
      isserver = true;
    }
    if (strcmp(argv[loop],"-p") == 0) {
      loop++;
      port = atoi(argv[loop]);
      
      if (port==0) {
        printf("Bad port");
        return -1;
      }
    }
  }

#ifdef _WIN32
  WSACleanup();
#endif
  return 0;
}