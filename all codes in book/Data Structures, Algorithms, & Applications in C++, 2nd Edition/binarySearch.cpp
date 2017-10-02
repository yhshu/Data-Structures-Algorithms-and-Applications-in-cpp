// binary search

#include <iostream>
#include <algorithm>

using namespace std;

template<class T>
int binarySearch(T a[], int n, const T& x)
{// Search a[0] <= a[1] <= ... <= a[n-1] for x.
 // Return position if found; return -1 otherwise.
   int left = 0;                       // left end of segment
   int right = n - 1;                  // right end of segment
   while (left <= right) {
      int middle = (left + right)/2;   // middle of segment
      if (x == a[middle]) return middle;
      if (x > a[middle]) left = middle + 1;
      else right = middle - 1;
      }
   return -1; // x not found
}

int main()
{
   int a[7] = {0, 2, 3, 4, 6, 7, 9};
   cout << binarySearch(a, 7, 4) << endl;
}
