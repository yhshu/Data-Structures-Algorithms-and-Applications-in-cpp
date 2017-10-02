// sequential search

#include <iostream.h>

template<class T>
int SequentialSearch(T a[], const T& x, int n)
{// Search the unordered list a[0:n-1] for x.
 // Return position if found; return -1 otherwise.
   if (n < 1) return -1;
   if (a[n-1] == x) return n - 1;
   return SequentialSearch(a, x, n-1);
}

void main(void)
{
   int a[7] = {0, 5, 3, 4, 7, 2, 6};
   cout << SequentialSearch(a, 4, 7) << endl;
}
