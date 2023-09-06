#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <string>

#include <list>
#include <iostream>
#include <thread>

#ifdef __WIN32__
# include <winsock2.h>
#else
# include <arpa/inet.h>
# include <sys/socket.h>
# include <cstring>
#endif
using namespace std;

/* options */
bool search = false;
char searchstr[35];
bool target = false;
char targethash[512];

/* variables */
string dir;
int argc;
char **argv;
list<char *> trackers;

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

int load_trackers() {
  FILE *f = fopen((dir+"\\trackerlist.txt").c_str(),"r");

  // TODO: mkdir does not work on linux
  if (f==NULL) {mkdir(dir.c_str());f = fopen((dir+"\\trackerlist.txt").c_str(),"w");}
  if (f==NULL) {
    printf("Cant read or make tracker list file at %s\n",(dir+"\\trackerlist.txt").c_str());
    return -3;
  }
  char *str = (char *) malloc(50);

  while (!feof(f)) {
    puts(fgets(str,50,f));
  }

  fclose(f);
  return 0;
}

int main(int argc_, char **argv_) {
  argc = argc_;
  argv = argv_;
  char *v;
#ifdef _WIN32
  WSADATA wsa;
  if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
    printf("Failed to initialize Winsock\n");
    return -1;
  }
  v = getenv("appdata");
#else
  v = getenv("home");
#endif
  // TODO: there is a cleaner way to make the dir str
  string directory = "\\ctrnt";
  dir = string(v);

  dir.append(directory);

  if (load_trackers()!=0) {
    return -3;
  }
  
  for (int loop=0;loop<argc;loop++) {
    if (strcmp(argv[loop], "-h")==0 | strcmp(argv[loop], "-help")==0) {
      printf("\ncrappytorrent 0 client\n-s <name> search for\n-d <hash> download from hash\n-test test trackers\n-t <protocol://address:port> add a tracker\n\n");
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
    if (strcmp(argv[loop], "-t")==0) {
      loop++;
      if (argv[loop] == NULL) {
        printf("Bad argument \"-t\"");
        return -3;
      }
      trackers.assign(1,argv[loop]);
    }
    if (strcmp(argv[loop], "-test")==0) {
      ;//...
    }
  }

#ifdef _WIN32
  WSACleanup();
#endif
  return 0;
}