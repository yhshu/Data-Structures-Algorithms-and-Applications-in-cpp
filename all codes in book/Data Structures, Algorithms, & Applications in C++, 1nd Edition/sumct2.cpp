// simplified step count of sum of n numbers

#include <iostream.h>

int count = 0;

template<class T>
T Sum(T a[], int n)
{// Return sum of numbers a[0:n - 1].
   for (int i = 0; i < n; i++)
      count += 2;
   count += 3; 
   return 0;
}

void main(void)
{
   float a[6] = {1, 2, 3, 4, 5, 6};
   cout << Sum(a,6) << endl;
   cout << count << endl;
}
