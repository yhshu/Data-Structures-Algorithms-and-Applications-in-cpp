// find min and max of n elements
// non-recursive divide-and-conquer version

#include <iostream.h>

template<class T>
bool MinMax(T w[], int n, T& Min, T& Max)
{// Locate min and max of w[0:n-1].
 // Return false if fewer than one element.
   // special cases, n <= 1
   if (n < 1) return false;
   if (n == 1) {Min = Max = 0; 
                return true;}

   // initialize Min and Max
   int s;  // start point for loop
   if (n % 2) {// n is odd
      Min = Max = 0;
      s = 1;}
   else {// n is even, compare first pair
         if (w[0] > w[1]) {
            Min = 1;
            Max = 0;}
         else {Min = 0;
               Max = 1;}
         s = 2;}

   // compare remaining pairs
   for (int i = s; i < n; i += 2) {
      // find larger of w[i] and w[i+1]
      // then compare larger with w[Max]
      // and smaller with w[Min]
      if (w[i] > w[i+1]) {
         if (w[i] > w[Max]) Max = i;
         if (w[i+1] < w[Min]) Min = i + 1;}
      else {
         if (w[i+1] > w[Max]) Max = i + 1;
         if (w[i] < w[Min]) Min = i;}
      }

   return true;
}

void main(void)
{
   int w[12] = {10, 25, 8, 2, 8, 10, 6, 3, 1, 20, 4, 35};
   int n = 12;
   int Min, Max;
   MinMax(w,n,Min,Max);
   cout << w[Min] << ' ' << w[Max] << endl;
}
