/*Nancy Tang Assignment 4 Client.cpp file
This file runs the client side of a client-server communication. The client
receives points on a graph as input and outputs the midpoint between two given
points and the distance between them.*/

#include "service.h"
#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

int main(int argc, char** argv) { 

   if (argc != 3) {
      printf("Invalid number of arguments.\n");
   }
   
   RPC* rpc = new RPC(argv[2], atoi(argv[1]));
   Service client;
   
   double temp;
   queue<double> input;
   while(cin >> temp) {
      input.push(temp);
   }
   
   cout << "P1" << setw(12) << "P2" << setw(12) << "distance" << setw(10) << "midpoint" << endl;
   while(!input.empty()) {
      Point* p1 = new Point();
      p1->x = input.front();
      input.pop();
      p1->y = input.front();
      input.pop();
      Point* p2 = new Point();
      p2->x = input.front();
      input.pop();
      p2->y = input.front();
      input.pop();
      Point* midpointResult = new Point();
      double* distanceResult = new double;
      if(client.midpoint(rpc, p1, p2, midpointResult) < 0) {
         cout << "Invalid point(s)" << endl;
      } else {
         client.cartesian_distance(rpc, p1, p2, distanceResult);
         cout << "(" << p1->x << ", " << p1->y << ")";
         cout << setw(12) << "(" << p2->x << ", " << p2->y << ")";
         cout << setw(12) << *distanceResult;
         cout << setw(10) << "(" << midpointResult->x << ", " << midpointResult->y << ")" << endl;
      }
      delete p1;
      delete p2;
      delete midpointResult;
      delete distanceResult;
   }
   delete rpc;
   return 0;
}