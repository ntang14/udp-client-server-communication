/*Nancy Tang Assignment 4 ServerService.h
This file contains the stub for a server. It takes apart the packets sent by
the client and updates information for the server. It also makes packets for
the server of information that needs to be sent back to the client.*/

#ifndef SERVERSERVICE_H
#define SERVERSERVICE_H

#include "RPC.h"
#include "Point.h"

class ServerService {
   public:
      int unmarshall(char buff[], Point* p1, Point* p2);
      void send(RPC* rpc, int result, double val1, double val2);
   private:
      int transactionId;
};

#endif