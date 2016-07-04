/*Nancy Tang Assignment 4 service.h
This file contains the class for a stub that works with a client to send a
request to a server and wait for a response. The stub updates information given
to it by the client based on information received from the server.*/

#ifndef SERVICE_H
#define SERVICE_H

#include "Point.h"
#include "RPC.h"

class Service {
   public:
      int cartesian_distance(RPC* rpc, Point* p1, Point* p2, double* result);
      int midpoint(RPC* rpc, Point* p1, Point* p2, Point* result);   
   private:
      int transactionId = 0;
};

#endif