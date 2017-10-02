
// functions for weighted directed graphs

#ifndef WDirected_
#define WDirected_

#include "network.h"
#include "dosmax.h"
#include <stdlib.h>

template <class T>
class WDirected : virtual public Network
{
   public:
      virtual void First(int i, int& j, T& c) = 0;
      virtual void Next(int i, int& j, T& c) = 0;
      T Longest(T L[], int kay[]);
      void OutputLongest(T L[], int kay[]);
};

template <class T>
T WDirected<T>::Longest(T L[], int kay[])
{// Return length of longest path.
 // Set L[i] to be length of longest path from vertex i.
 // kay[i] is next vertex on longest path from vertex i.
   int n = Vertices();
   int MaxLength = 0;  // length of longest path
   InitializePos();    // graph iterators

   for (int i = n; i > 0; i--) {
      // compute L[i] and kay[i]
      L[i] = 0;
      kay[i] = 0;
      int j;  // vertex adjacent from i
      T c;    // cost of edge (i,j)
      First(i,j,c);
      while (j) {// there is an adjacent vertex
         if (j <= i)
            // improper digraph or vertex numbering
            // j should be > i
            throw BadInput();

         if (L[i] < c + L[j]) {
            // path though j is longer
            L[i] = c + L[j];
            kay[i] = j;
            }
         Next(i,j,c);
         }
      MaxLength = max(MaxLength, L[i]);
      }

   DeactivatePos();
   return MaxLength;
}

template <class T>
void WDirected<T>::OutputLongest(T L[], int kay[])
{// Output the longest path using L and kay as
 // computed by Longest.
   int n = Vertices();

   // find start vertex of longest path
   // this is vertex with maximum L[]
   int start = 1;
   for (int i = 2; i <= n; i++)
      if (L[i] > L[start])
         start = i;

   // now output the path
   while (start) {
      cout << start << " ";
      start = kay[start];
      }
   cout << endl;
}
   

#endif;
