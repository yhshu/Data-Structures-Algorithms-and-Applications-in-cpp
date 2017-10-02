#ifndef RandomPermutation_
#define RandomPermutation_

#include <stdlib.h>
#include "swap.h"

template<class type>
void Permute(type *a, int n)
{// Random permutation generator.
for (int i = n-1; i > 0; i--) {
   int j = rand() * i; //select an element from a[0] to a[i]
   Swap(a[i], a[j]);}
}

#endif
