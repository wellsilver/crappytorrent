#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <unistd.h>
#ifdef __WIN32__
# include <winsock2.h>
#else
# include <arpa/inet.h>
# include <sys/socket.h>
#endif
using namespace std;

// a info packet
struct ackpacket {
  char type;
  int64_t ip;

} __attribute__((__packed__));

// a download packet
struct downpacket {
  char type;
  int64_t ip;

  char data[100];
} __attribute__((__packed__));

// a search packet {
struct searchpacket {
  char type;
  int64_t ip;

  char string[32]; // what to search for

} __attribute__((__packed__));

void server() {
  int fd;
  int opt = 1;
  int rslt;

  fd = socket(AF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(4079);

  rslt = bind(fd, (struct sockaddr*)&address, sizeof(address));

  if (rslt == -1) {
    printf("- server could not bind %i\n", errno);
    close(fd);
    return;
  }

  close(fd);
}

int main() {
#ifdef _WIN32
  WSADATA wsa;
  if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
      printf("Failed to initialize Winsock\n");
      return 1;
  }
#endif

  thread th(server);
  th.join();

#ifdef _WIN32
WSACleanup();
#endif
  return 0;
}