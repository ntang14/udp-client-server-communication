/*Nancy Tang Assignment 4 Server.cpp
This file runs the server side of a client-server connection. The server takes
in information about two points and will return either the distance between the
two points or the midpoint of the points, depending on what the client asks
for.*/

#include "ServerService.h"
#include <math.h>

using namespace std;

int distance(Point* p1, Point* p2, double* result) {
   *result = sqrt(pow((p2->x - p1->x), 2) + pow((p2->y - p1->y), 2));
   return 0;
}

int midpoint(Point* p1, Point* p2, Point* result) {
   result->x = (p1->x + p2->x) / 2;
   result->y = (p1->y + p2->y) / 2;
   return 0;
}

int main(int argc, char** argv) {
   
   if(argc != 2) {
      printf("Invalid number of arguments.\n");
      return -1;
   }
   
   RPC* rpc = new RPC(atoi(argv[1]));
   ServerService server;
   
   for(;;) {
      Point* p1 = new Point();
      Point* p2 = new Point();
      char data[40];
      rpc->recv(data, 40);
      int operation;
      operation = server.unmarshall(data, p1, p2);
      if(p1->y < 0 || p2->y < 0) {
         server.send(rpc, -1, -1, -1);
      } else if(p1->x >= 0 && p2->x >= 0) {
         if(operation == 0) { // midpoint
            Point* result = new Point();
            midpoint(p1, p2, result);
            server.send(rpc, 0, result->x, result->y);
            delete result;
         } else {
            double* result = new double;
            distance(p1, p2, result);
            server.send(rpc, 0, *result, -1);
            delete result;
         }
      }
      delete p1;
      delete p2;
   }
   delete rpc;
   return 0;
}