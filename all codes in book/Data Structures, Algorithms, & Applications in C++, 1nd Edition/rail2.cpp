// railroad car rearrangement using queues

#include <iostream.h>
#include "lqueue.h"

void Output(int& minH, int& minQ,
        LinkedQueue<int> H[], int k, int n)
{// Move from hold to output and update minH and minQ.
   int c;  // car index

   // delete smallest car minH from queue minQ
   H[minQ].Delete(c);
   cout << "Move car " << minH << " from holding track "
        << minQ << " to output" << endl;

   // find new minH and minQ
   // by checking front of all queues
   minH = n + 2;
   for (int i = 1; i <= k; i++)
      if (!H[i].IsEmpty() &&
                (c = H[i].First()) < minH) {
          minH = c;
          minQ = i;}
}

bool Hold(int c, int& minH, int &minQ,
	LinkedQueue<int> H[], int k)
{// Add car c to a holding track.
 // Return false if no feasible holding track.
 // Throw NoMem exception if no queue space.
 // Return true otherwise.

   // find best holding track for car c
   // initialize
   int BestTrack = 0,  // best track so far
       BestLast = 0,   // last car in BestTrack
       x;              // a car index

   // scan holding tracks
   for (int i = 1; i <= k; i++)
      if (!H[i].IsEmpty()) {// track i not empty
         x = H[i].Last();
         if (c > x && x > BestLast) {
            // track i has bigger car at end
   	    BestLast = x;
            BestTrack = i;}
         }
      else // track i empty
         if (!BestTrack) BestTrack = i;
      
   if (!BestTrack) return false; // no track available
   
   // add c to best track
   H[BestTrack].Add(c);
   cout << "Move car " << c << " from input "
        << "to holding track " << BestTrack << endl;

   // update minH and minQ if needed
   if (c < minH) {minH = c;
                  minQ = BestTrack;}

   return true;
}

bool Railroad(int p[], int n, int k)
{// k track rearrangement of car order p[1:n].
 // Return true if successful, false if impossible.
 // Throw NoMem exception if inadequate space.

   // create queues for holding tracks
   LinkedQueue<int> *H;
   H = new LinkedQueue<int> [k];
   k--; // keep track k open for direct moves

   int NowOut = 1;   // next car to output
   int minH = n+1;   // smallest car in a track
   int minQ;         // track with car minH

   // rearrange cars
   for (int i = 1; i <= n; i++)
      if (p[i] == NowOut) {// send straight out
         cout << "Move car " << p[i] <<
                 " from input to output" << endl;
         NowOut++;

         // output from holding tracks
         while (minH == NowOut) {
            Output(minH, minQ, H, k, n);
   	    NowOut++;
            }
         }
      else {// put car p[i] in a holding track
         if (!Hold(p[i], minH, minQ, H, k))
         return false;}

   return true;
}

void main(void)
{
   // int p[10] = {0, 5, 8, 1, 7, 4, 2, 9, 6, 3};
   int p[10] = {0, 3, 6, 9, 2, 4, 7, 1, 8, 5};
   cout << "Input permutation is 0369247185" << endl;
   Railroad(p,9,3);
}
