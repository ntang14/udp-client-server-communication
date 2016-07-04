/*Nancy Tang Assignment 4 RPC.h
This file contains the class for an RPC that services both the client and the
server side. It creates a socket for whichever one is needed and allows either
to send and receive messages.*/

#ifndef RPC_H
#define RPC_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>

#define BUFSIZE 1024

class RPC {

   public:
      RPC(char address[], int port); // client
      RPC(int port); // server
      ~RPC();
      void send(char buff[], int size);
      int recv(char buff[], int size);
      int max_retries = 3;
   
   private:
      int clientId = -1;
      int serverId = -1;
      struct sockaddr_in addr;
      int port;
      int timeout = 5;
      char address[BUFSIZE];
      unsigned int addrsize;
      struct sockaddr newaddr;

};

#endif