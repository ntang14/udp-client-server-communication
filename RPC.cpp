/*Nancy Tang Assignment 4 RPC.cpp
This file contains the functions for an RPC that services both the client and the
server side. It creates a socket for whichever one is needed and allows either
to send and receive messages.*/

#include "RPC.h"

using namespace std;

RPC::RPC(char address[], int port) {
   this->port = port;
   strncpy(this->address, address, BUFSIZE);
   clientId = socket(AF_INET, SOCK_DGRAM, 0);
   struct in_addr add;
   inet_aton(address, &add);
   addrsize = sizeof(addr);
   bzero(&addr, sizeof(addr));
   addr.sin_family = AF_INET;
   addr.sin_addr = add;
   addr.sin_port = htons(port);
}

RPC::RPC(int port) {
   this->port = port;
   serverId = socket(AF_INET, SOCK_DGRAM, 0);
   bzero(&addr, sizeof(addr));
   addr.sin_family = AF_INET;
   addr.sin_port = htons(port);
   addr.sin_addr.s_addr = htonl(INADDR_ANY);
   addrsize = sizeof(addr);
   if (bind(serverId, (struct sockaddr *) &addr, addrsize) < 0) {
      perror("bind failed");
   }
}

RPC::~RPC() {
   if(clientId != -1) {
      close(clientId);
   } else {
      close(serverId);
   }
}

void RPC::send(char buff[], int size) {
   if(clientId == -1) {
      if(sendto(serverId, buff, size, 0, (struct sockaddr*) &newaddr, sizeof(newaddr)) < 0) {
         perror("sendto");
      }
   } else {
      if(sendto(clientId, buff, size, 0, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
         perror("client sendto");
      }
   }
}

int RPC::recv(char buff[], int size) {
   socklen_t addrlen = sizeof(newaddr);
   bzero((char*) &newaddr, addrlen);
   if(clientId == -1) {
      if(recvfrom(serverId, buff, size, 0, &newaddr, &addrlen) < 0) {
         perror("receiving from socket");
         return -1;
      }
   } else {
      struct timeval tv;
      tv.tv_sec = timeout;
      tv.tv_usec = 0;
      setsockopt(clientId, SOL_SOCKET, SO_RCVTIMEO,(struct timeval *)&tv,sizeof(struct timeval));
      if(recvfrom(clientId, buff, size, 0, &newaddr, &addrlen) < 0) {
         perror("timed out, trying again");
         return -1;
      }
   }
   return 0;
}