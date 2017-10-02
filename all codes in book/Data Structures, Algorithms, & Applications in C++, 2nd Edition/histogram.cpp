// simple histogramming program

#include <iostream>

using namespace std;

void main(void)
{// Histogram of nonnegative integer values.
   int n,  // number of elements
       r;  // values between 0 and r
   cout << "Enter number of elements and range"
        << endl;
   cin >> n >> r;

   // create histogram array h
   int *h = new int[r+1];

   // initialize array h to zero
   for (int i = 0; i <= r; i++)
      h[i] = 0;

   // input data and compute histogram
   for (i = 1; i <= n; i++)
   {// assume input values are between 0 and r
      int key;  // input value
      cout << "Enter element " << i << endl;
      cin >> key;
      h[key]++;
   }

   // output histogram
   cout << "Distinct elements and frequencies are"
        << endl;
   for (i = 0; i <= r; i++)
      if (h[i] != 0)
         cout << i << "   "  << h[i] << endl;
}
