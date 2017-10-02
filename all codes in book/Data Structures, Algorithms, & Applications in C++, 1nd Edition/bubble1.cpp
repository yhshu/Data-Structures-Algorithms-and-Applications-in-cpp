// bubble sort

#include <iostream.h>
#include "swap.h"

template<class T>
void Bubble(T a[], int n)
{// Bubble largest element in a[0:n-1] to right.
   for (int i = 0; i < n - 1; i++)
      if (a[i] > a[i+1]) Swap(a[i], a[i + 1]);
}

template<class T>
void BubbleSort(T a[], int n)
{// Sort a[0:n - 1] using bubble sort.
   for (int i = n; i > 1; i--)
      Bubble(a, i);
}

void main(void)
{
   int y[10] = {10,7,8,9,4, 2, 3, 6, 5,1};
   BubbleSort(y,10);
   for (int i = 0; i < 10; i++)
      cout << y[i] << ' ';
   cout << endl;
}
