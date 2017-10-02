// find location of maximum of n numbers

#include "myExceptions.h"

using namespace std;

template<class T>
int indexOfMax(T a[], int n)
{// Locate the largest element in a[0:n-1].
   if (n <= 0)
      throw illegalParameterValue("n must be > 0");

   int indexOfMax = 0;
   for (int i = 1; i < n; i++)
     if (a[indexOfMax] < a[i])
        indexOfMax = i;
   return indexOfMax;
}
