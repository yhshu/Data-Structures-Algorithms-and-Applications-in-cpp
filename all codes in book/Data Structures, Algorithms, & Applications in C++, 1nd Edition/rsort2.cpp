// rank sort without additional array

#include <iostream.h>
#include "swap.h"

template<class T>
void Rank(T a[], int n, int r[])
{// Rank the n elements a[0:n-1].
   for (int i = 0; i < n; i++)
      r[i] = 0;  // initialize

   // compare all element pairs
   for (i = 1; i < n; i++)
      for (int j = 0; j < i; j++)
         if (a[j] <= a[i]) r[i]++;
         else r[j]++;
}

template<class T>
void Rearrange(T a[], int n, int r[])
{// In-place rearrangement into sorted order.
   for (int i = 0; i < n; i++)
      // get proper element to a[i]
      while (r[i] != i) {
         int t = r[i];
         Swap(a[i], a[t]);
         Swap(r[i], r[t]);
         }
}

void main(void)
{
   int a[6] = {2, 6, 4, 3, 1, 5};
   int r[6];
   int n = 6;
   Rank(a,n,r);
   Rearrange(a,n,r);
   for (int i = 0; i < n; i++)
      cout << a[i] << ' ';
   cout << endl;
}
