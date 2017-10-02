
// randomly permute an array

#ifndef Permute_
#define Permute_

#include <stdlib.h>
#include "swap.h"

template <class T>
void Permute(T a[], int n)
{// Permute a[0:n-1].

   for (int i = n - 1; i > 0; i--)
      // swap a[i] with a randomly selected element
      // from a[0:i]
      Swap(a[i], a[rand() * i]);
}

#endif
