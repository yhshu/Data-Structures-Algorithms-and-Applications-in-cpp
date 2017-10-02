
// histogramming by sorting

#include <iostream.h>
#include <stdlib.h>
#include "hsort.h"

void main(void)
{// Histogram using a search tree.
   int *E; // 1D array of elements
   int n;  // number of elements
   cout << "Enter number of elements" << endl;
   cin >> n;

   // create the array E[0:n+1]
   try {E = new int [n+1];}
   catch (...)
      {cout << "Insufficient Memory" << endl;
       exit(1);}

   // input elements into the array E
   for (int i = 1; i <= n; i++) {
      cout << "Enter element " << i << endl;
      cin >> E[i];
      }

   // sort the elements
   HeapSort(E,n);  

   // output distinct elements and their counts
   cout << "Distinct elements and frequencies are"
        << endl;
   int c = 1;  // cursor into E
   while (c <= n) {
      // new element at E[c]
      // scan over elements equal to E[c]
      int j = c + 1;
      while (j <= n && E[j] == E[c])
         j++;

      // number of elements equal to E[c] is j - c
      cout << E[c] << " " << (j - c) << "    ";

      // set c to next new element
      c = j;
   }
   cout << endl;
}
