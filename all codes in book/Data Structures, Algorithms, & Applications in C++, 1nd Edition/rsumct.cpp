// step count for recursive sum of n numbers

#include <iostream.h>
int count = 0;

template<class T>
T Rsum(T a[], int n)
{// Return sum of numbers a[0:n - 1].
   count++; // for if conditional
   if (n > 0) {count++; // for return and Rsum invocation
               return Rsum(a, n-1) + a[n-1];}
   count++; // for return
   return 0;
}

void main(void)
{
   float a[6] = {1, 2, 3, 4, 5, 6};
   cout << Rsum(a,6) << endl;
   cout << count << endl;
}
