// railroad car rearrangement using stacks

#include <iostream.h>
#include "lstack.h"

void Output(int& minH, int& minS,
        LinkedStack<int> H[], int k, int n)
{// Move from hold to output and update minH and minS.
   int c;  // car index

   // delete smallest car minH from stack minS
   H[minS].Delete(c);
   cout << "Move car " << minH << " from holding track "
        << minS << " to output" << endl;

   // find new minH and minS
   // by checking top of all stacks
   minH = n + 2;
   for (int i = 1; i <= k; i++)
      if (!H[i].IsEmpty() &&
                (c = H[i].Top()) < minH) {
         minH = c;
         minS = i;}
}

bool Hold(int c, int& minH, int &minS,
        LinkedStack<int> H[], int k, int n)
{// Add car c to a holding track.
 // Return false if no feasible holding track.
 // Throw NoMem exception if no stack space.
 // Return true otherwise.

   // find best holding track for car c
   // initialize
   int BestTrack = 0,    // best track so far
       BestTop = n + 1,  // top car in BestTrack
       x;                // a car index

   // scan tracks
   for (int i = 1; i <= k; i++)
      if (!H[i].IsEmpty()) {// track i not empty
         x = H[i].Top();
         if (c < x && x < BestTop) {
            // track i has smaller car at top
            BestTop = x;
            BestTrack = i;}
         }
      else // track i empty
         if (!BestTrack) BestTrack = i;
      
   if (!BestTrack) return false; // no feasible track

   // add c to best track
   H[BestTrack].Add(c);
   cout << "Move car " << c << " from input "
        << "to holding track " << BestTrack << endl;

   // update minH and minS if needed
   if (c < minH) {minH = c;
                  minS = BestTrack;}

   return true;
}

bool Railroad(int p[], int n, int k)
{// k track rearrangement of car order p[1:n].
 // Return true if successful, false if impossible.
 // Throw NoMem exception if inadequate space.

   // create stacks for holding tracks
   LinkedStack<int> *H;
   H = new LinkedStack<int> [k + 1];

   int NowOut = 1;  // next car to output
   int minH = n+1;  // smallest car in a track
   int minS;        // track with car minH

   // rearrange cars
   for (int i = 1; i <= n; i++)
      if (p[i] == NowOut) {// send straight out
         cout << "Move car " << p[i] <<
                 " from input to output" << endl;
         NowOut++;

         // output from holding tracks
         while (minH == NowOut) {
            Output(minH, minS, H, k, n);
   	    NowOut++;
            }
         }
      else {// put car p[i] in a holding track
         if (!Hold(p[i], minH, minS, H, k, n))
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
