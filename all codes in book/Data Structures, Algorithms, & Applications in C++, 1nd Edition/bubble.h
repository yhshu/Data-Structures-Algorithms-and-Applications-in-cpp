
#include "swap.h"
#include "max.h"

template<class type>
void SelectionSort(type *a, int n)
{// Sort the n elements a[0:n-1].
   for (int size = n; size > 1; size--) {
     int j = max(a, size);
     swap(a[j], a[size - 1]);}
}

