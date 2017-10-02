// ineffficient prefix sums

#include <iostream.h>

template <class T>
T Sum(T a[], int n)
{// Return sum of numbers a[0:n - 1].
   T tsum = 0;
   for (int i = 0; i < n; i++)
      tsum += a[i];
   return tsum;
}

template <class T>
void Inef(T a[], T b[], int n)
{// Compute prefix sums.
   for (int j = 0; j < n; j++)
      b[j] = Sum(a, j + 1);
}

void main(void)
{
   int a[6] = {1, 2, 3, 4, 5, 6};
   int b[6];
   int n = 6;
   Inef(a,b,n);
   for (int i = 0; i < n; i++)
      cout << b[i] << ' ';
   cout << endl;
}
