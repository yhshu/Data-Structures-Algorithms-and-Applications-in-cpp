// railroad car rearrangement with LIFO holding tracks
// no explicit queues used

#include <iostream.h>
#include "xcept.h"

void Output(int NowOut, int Track, int& Last)
{// Move car NowOut from hold to output and update Last.
   cout << "Move car " << NowOut
        << " from holding track "
        << Track << " to output" << endl;
   if (NowOut == Last) Last = 0;
}

bool Hold(int c, int last[], int track[], int k)
{// Add car c to a holding track.
 // Return false if no feasible holding track.
 // Return true otherwise.

   // find best holding track for car c
   // initialize
   int BestTrack = 0,  // best track so far
       BestLast = 0;   // last car in BestTrack

   // scan holding tracks
   for (int i = 1; i <= k; i++) // find best track
      if (last[i]) {// track i not empty
         if (c > last[i] && last[i] > BestLast) {
            // track i has bigger car at end
   	    BestLast = last[i];
            BestTrack = i;}
         }
      else // track i empty
         if (!BestTrack) BestTrack = i;
      
   if (!BestTrack) return false; // no track available
   
   // add c to best track
   track[c] = BestTrack;
   last[BestTrack] = c;
   cout << "Move car " << c << " from input "
        << "to holding track " << BestTrack << endl;

   return true;
}

bool Railroad(int p[], int n, int k)
{// k track rearrangement of car order p[1:n].
 // Return true if successful, false if impossible.
 // Throw NoMem exception if inadequate space.

   // initialize arrays last and track
   int *last = new int [k + 1];
   int *track = new int [n + 1];
   for (int i = 1; i <= k; i++)
      last[i] = 0;  // track i is empty
   for (i = 1; i <= n; i++)
      track[i] = 0;  // car i is on no track
   k--; // keep track k open for direct moves
   
   // initialize index of next car
   // that goes to output
   int NowOut = 1;

   // output cars in order
   for (i = 1; i <= n; i++)
      if (p[i] == NowOut) {// send straight to output
         cout << "Move car " << p[i] <<
                 " from input to output" << endl;
         NowOut++;

         // output from holding tracks
         while (NowOut <= n && track[NowOut]) {
            Output(NowOut, track[NowOut], last[NowOut]);
   	    NowOut++;
            }
         }
      else {// put car p[i] in a holding track
         if (!Hold(p[i], last, track, k))
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
