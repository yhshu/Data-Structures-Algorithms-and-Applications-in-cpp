// recursive sum of n numbers

#include <iostream.h>

template<class T>
T Rsum(T a[], int n)
{// Return sum of numbers a[0:n - 1].
   if (n > 0)
      return Rsum(a, n-1) + a[n-1];
   return 0;
}

void main(void)
{
   int a[6] = {1, 2, 3, 4, 5, 6};
   cout << Rsum(a,6) << endl;
}
