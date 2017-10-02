// step count for sum of n numbers

#include <iostream.h>

int count = 0;

template<class T>
T Sum(T a[], int n)
{// Return sum of numbers a[0:n - 1].
   T tsum = 0;
   count++; // for tsum = 0
   for (int i = 0; i < n; i++) {
     count++; // for the for statement
     tsum += a[i];
     count++; // for assignment
     }
   count++; // for last execution of for statement
   count++; // for return
   return tsum;
}

void main(void)
{
   float a[6] = {1, 2, 3, 4, 5, 6};
   cout << Sum(a,6) << endl;
   cout << count << endl;
}
