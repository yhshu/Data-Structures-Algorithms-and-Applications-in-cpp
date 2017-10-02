// sequential search of sorted array

#include <iostream.h>

template<class T>
int SequentialSearch(T a[], const T& x, int n)
{// Search the unordered list a[0:n-1] for x.
 // Return position if found; return -1 otherwise.
   a[n] = x; // assume extra position available
   int i;
   for (i = 0; a[i] != x; i++);
   if (i == n) return -1;
   return i;
}

void main(void)
{
   // a[7] is not used
   int a[8] = {0, 5, 3, 4, 7, 2, 6, 0};
   cout << SequentialSearch(a, 4, 7) << endl;
}
