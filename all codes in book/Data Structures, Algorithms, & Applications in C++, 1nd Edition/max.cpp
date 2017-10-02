// find maximum of n numbers

#include <iostream.h>

template<class T>
int Max(T a[], int n)
{// Locate the largest element in a[0:n-1].
   int pos = 0;
   for (int i = 1; i < n; i++)
     if (a[pos] < a[i])
        pos = i;
   return pos;
}

void main(void)
{
   float a[6] = {1, 2, 3, 4, 5, 6};
   cout << Max(a,6) << endl;
}
