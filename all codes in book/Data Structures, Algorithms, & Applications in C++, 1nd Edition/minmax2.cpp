// find min and max of n elements

#include <iostream.h>

template<class T>
bool MinMax(T a[], int n, int& Min, int& Max)
{// Locate min and max elements in a[0:n-1].
 // Return false if less than one element.
   if (n < 1) return false;
   Min = Max = 0; // initial guess
   for (int i = 1; i < n; i++)
      if (a[Min] > a[i]) Min = i;
      else if (a[Max] < a[i]) Max = i;
   return true;
}

void main(void)
{
   int a[6] = {2, 6, 4, 3, 1, 5};
   int n = 6, Min, Max;
   MinMax(a,n,Min,Max);
   cout << Min << ' ' << Max << endl;
}
