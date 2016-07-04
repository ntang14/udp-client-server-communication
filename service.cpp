/*Nancy Tang Assignment 4 service.cpp file
This file contains the functions for a stub that works with a client to send a
request to a server and wait for a response. The stub updates information given
to it by the client based on information received from the server.*/

#include "service.h"

using namespace std;

int Service::cartesian_distance(RPC* rpc, Point* p1, Point* p2, double* result) {
   transactionId++;
   char arguments[40];
   int ids[] = {transactionId, 1};
   double parameters[] = {p1->x, p1->y, p2->x, p2->y};
   char source1[8];
   memcpy(source1, ids, 8);
   char source2[32];
   memcpy(source2, parameters, 32);
   memcpy(arguments, source1, 8);
   memcpy(&arguments[8], source2, 32);
   rpc->send(arguments, 40);
   
   char results[16];
   int retries = 0;
   if(rpc->recv(results, 16) < 0) {
      if(retries == rpc->max_retries) {
         return -1;
      } else {
         retries++;
         rpc->send(arguments, 40);
      }
   }
   int temp[2];
   double temp2[1];
   memcpy(temp, results, 8);
   memcpy(temp2, &results[8], 8);
   if(temp[1] == -1 || temp[0] != transactionId) {
      return -1;
   } else {
      *result = temp2[0];
      return 0;
   }
}

int Service::midpoint(RPC* rpc, Point* p1, Point* p2, Point* result) {
   transactionId++;
   char arguments[40];
   int ids[] = {transactionId, 0};
   double parameters[] = {p1->x, p1->y, p2->x, p2->y};
   char source1[8];
   memcpy(source1, ids, 8);
   char source2[32];
   memcpy(source2, parameters, 32);
   memcpy(arguments, source1, 8);
   memcpy(&arguments[8], source2, 32);
   rpc->send(arguments, 40);
   
   char results[24];
   rpc->recv(results, 24);
   int temp[2];
   double temp2[2];
   memcpy(temp, results, 8);
   memcpy(temp2, &results[8], 16);
   if(temp[1] == -1 || temp[0] != transactionId) {
      return -1;
   } else {
      result->x = temp2[0];
      result->y = temp2[1];
      return 0;
   }
}