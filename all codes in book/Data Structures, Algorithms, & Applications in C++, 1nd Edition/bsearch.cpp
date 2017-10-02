// binary search

#include <iostream.h>

template<class T>
int BinarySearch(T a[], const T& x, int n)
{// Search a[0] <= a[1] <= ... <= a[n-1] for x.
 // Return position if found; return -1 otherwise.
   int left = 0; int right = n - 1;
   while (left <= right) {
      int middle = (left + right)/2;
      if (x == a[middle]) return middle;
      if (x > a[middle]) left = middle + 1;
      else right = middle - 1;
      }
   return -1; // x not found
}

void main(void)
{
   int a[7] = {0, 2, 3, 4, 6, 7, 9};
   cout << BinarySearch(a, 4, 7) << endl;
}
