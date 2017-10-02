// railroad car rearrangement using no explicit queues
#include <iostream>

using namespace std;

// global variables
int* whichTrack;  // track that has the car
int* lastCar;     // last car in track
int numberOfCars;
int numberOfTracks;

void outputFromHoldingTrack(int c)
{// Move car c from its holding track to the output track.
   cout << "Move car " << c << " from holding track "
        << whichTrack[c] << " to output track" << endl;

   // if c was the last car in its track, the track is now empty
   if (c == lastCar[whichTrack[c]])
      lastCar[whichTrack[c]] = 0;
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
      if (lastCar[i] != 0)
      {// track i not empty
          if (c > lastCar[i] && lastCar[i] > bestLast)
          {
             // track i has bigger car at its rear
             bestLast = lastCar[i];
             bestTrack = i;
          }
      }
      else // track i empty
         if (bestTrack == 0)
            bestTrack = i;
      
   if (bestTrack == 0)
      return false; // no feasible track

   // add c to bestTrack
   whichTrack[c] = bestTrack;
   lastCar[bestTrack] = c;
   cout << "Move car " << c << " from input track "
        << "to holding track " << bestTrack << endl;

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

   // create the arrays lastCar and whichTrack
   lastCar = new int [numberOfTracks + 1];
   fill(lastCar + 1, lastCar + numberOfTracks + 1, 0);
   whichTrack = new int [numberOfCars + 1];
   fill(whichTrack + 1, whichTrack + numberOfCars + 1, 0);

   int nextCarToOutput = 1;

   // rearrange cars
   for (int i = 1; i <= numberOfCars; i++)
      if (inputOrder[i] == nextCarToOutput)
      {// send car inputOrder[i] straight out
          cout << "Move car " << inputOrder[i] << " from input "
               << "track to output track" << endl;
          nextCarToOutput++;
 
          // output from holding tracks
          while (nextCarToOutput <= numberOfCars &&
                 whichTrack[nextCarToOutput] != 0)
          {
             outputFromHoldingTrack(nextCarToOutput);
    	     nextCarToOutput++;
         }
      }
      else
      // put car inputOrder[i] in a holding track
         if (!putInHoldingTrack(inputOrder[i]))
            return false;

   return true;
}

int main()
{
   //int p[] = {0, 5, 8, 1, 7, 4, 2, 9, 6, 3};
   //cout << "Input permutation is 581742963" << endl;
   int p[] = {0, 3, 6, 9, 2, 4, 7, 1, 8, 5};
   cout << "Input permutation is 369247185" << endl;
   railroad(p, 9, 3);

   return 0;
}
