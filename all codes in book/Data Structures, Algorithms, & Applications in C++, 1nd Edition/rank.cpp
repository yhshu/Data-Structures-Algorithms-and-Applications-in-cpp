// compute element ranks

#include <iostream.h>

template<class T>
void Rank(T a[], int n, int r[])
{// Rank the n elements a[0:n-1].
   for (int i = 0; i < n; i++)
      r[i] = 0;  // initialize
   // compare all element pairs
   // Visual complains if we say int i again
   for (i = 1; i < n; i++)
      for (int j = 0; j < i; j++)
         if (a[j] <= a[i]) r[i]++;
         else r[j]++;
}

void main(void)
{
   int a[6] = {2, 6, 4, 3, 1, 5};
   int r[6];
   int n = 6;
   Rank(a,n,r);
   for (int i = 0; i < n; i++)
      cout << r[i] << ' ';
   cout << endl;
}
