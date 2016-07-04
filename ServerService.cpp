/*Nancy Tang Assignment 4 ServerService.cpp
This file contains the stub for a server. It takes apart the packets sent by
the client and updates information for the server. It also makes packets for
the server of information that needs to be sent back to the client.*/

#include "ServerService.h"

using namespace std;

int ServerService::unmarshall(char buff[], Point* p1, Point* p2) {
   int temp[2];
   double temp2[4];
   memcpy(temp, buff, 8);
   memcpy(temp2, &buff[8], 32);
   p1->x = temp2[0];
   p1->y = temp2[1];
   p2->x = temp2[2];
   p2->y = temp2[3];
   transactionId = temp[0];
   return temp[1];
}

void ServerService::send(RPC* rpc, int result, double val1, double val2) {
   if(val2 < 0) {
      char arguments[16];
      int temp[] = {transactionId, result};
      double temp2[] = {val1};
      char source[8];
      memcpy(source, temp, 8);
      char source2[8];
      memcpy(source2, temp2, 8);
      memcpy(arguments, source, 8);
      memcpy(&arguments[8], source2, 8);
      rpc->send(arguments, 16);
   } else {
      char arguments[24];
      int temp[] = {transactionId, result};
      double temp2[] = {val1, val2};
      char source[8];
      memcpy(source, temp, 8);
      char source2[16];
      memcpy(source2, temp2, 16);
      memcpy(arguments, source, 8);
      memcpy(&arguments[8], source2, 16);
      rpc->send(arguments, 24);
   }
}