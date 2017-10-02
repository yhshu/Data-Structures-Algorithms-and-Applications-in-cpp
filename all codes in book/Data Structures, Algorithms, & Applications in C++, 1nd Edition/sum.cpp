// sum n numbers

#include<iostream.h>

template<class T>
T Sum(T a[], int n)
{// Return sum of numbers a[0:n -1].
   T tsum = 0;
   for (int i = 0; i < n; i++)
      tsum += a[i];
   return tsum;
}

void main(void)
{
   int a[6] = {1, 2, 3, 4, 5, 6};
   cout << Sum(a,6) << endl;
}
