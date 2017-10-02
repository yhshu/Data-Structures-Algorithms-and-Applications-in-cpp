
// railroad car rearrangement using queues

#include <iostream>
#include "arrayQueue.h"

using namespace std;


// global variables
arrayQueue<int>* track;      // array of holding tracks
int numberOfCars;
int numberOfTracks;
int smallestCar;        // smallest car in any holding track
int itsTrack;           // holding track with car smallestCar

void outputFromHoldingTrack()
{// output the smallest car from the holding tracks
   // pop smallestCar from itsTrack
   track[itsTrack].pop();
   cout << "Move car " << smallestCar << " from holding track "
        << itsTrack << " to output track" << endl;

   // find new smallestCar and itsTrack by checking all queue fronts
   smallestCar = numberOfCars + 2;
   for (int i = 1; i <= numberOfTracks; i++)
      if (!track[i].empty() && track[i].front() < smallestCar)
      {
         smallestCar = track[i].front();
         itsTrack = i;
      }
}


bool putInHoldingTrack(int c)
{// Put car c into a holding track.
 // Return false iff there is no feasible holding track for this car.

   // find best holding track for car c
   // initialize
   int bestTrack = 0,  // best track so far
       bestLast =  0;  // last car in bestTrack

   // scan tracks
   for (int i = 1; i <= numberOfTracks; i++)
      if (!track[i].empty())
      {// track i not empty
          int lastCar = track[i].back();
          if (c > lastCar && lastCar > bestLast)
          {
             // track i has bigger car at its rear
             bestLast = lastCar;
             bestTrack = i;
          }
      }
      else // track i empty
         if (bestTrack == 0)
            bestTrack = i;
      
   if (bestTrack == 0)
      return false; // no feasible track

   // add c to bestTrack
   track[bestTrack].push(c);
   cout << "Move car " << c << " from input track "
        << "to holding track " << bestTrack << endl;

   // update smallestCar and itsTrack if needed
   if (c < smallestCar)
   {   
       smallestCar = c;
       itsTrack = bestTrack;
   }

   return true;
}

bool railroad(int* inputOrder,
              int theNumberOfCars, int theNumberOfTracks)
{// Rearrange railroad cars beginning with the initial order.
 // inputOrder[1:theNumberOfCars]
 // Return true if successful, false if impossible.

   numberOfCars = theNumberOfCars;
   // keep last track open for output
   numberOfTracks = theNumberOfTracks - 1;

   // create queues track[1:numberOfTracks] for use as holding tracks
   track = new arrayQueue<int> [numberOfTracks + 1];

   int nextCarToOutput = 1;
   smallestCar = numberOfCars + 1;  // no car in holding tracks

   // rearrange cars
   for (int i = 1; i <= numberOfCars; i++)
      if (inputOrder[i] == nextCarToOutput)
      {// send car inputOrder[i] straight out
          cout << "Move car " << inputOrder[i] << " from input "
               << "track to output track" << endl;
          nextCarToOutput++;
 
          // output from holding tracks
          while (smallestCar == nextCarToOutput)
          {
             outputFromHoldingTrack();
    	     nextCarToOutput++;
         }
      }
      else
      // put car inputOrder[i] in a holding track
         if (!putInHoldingTrack(inputOrder[i]))
            return false;

   return true;
}

// test program
int main()
{
   //int p[] = {0, 5, 8, 1, 7, 4, 2, 9, 6, 3};
   //cout << "Input permutation is 581742963" << endl;
   int p[] = {0, 3, 6, 9, 2, 4, 7, 1, 8, 5};
   cout << "Input permutation is 369247185" << endl;
   railroad(p, 9, 3);

   return 0;
}
