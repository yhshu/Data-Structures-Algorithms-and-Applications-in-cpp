// insertion sort

#include <iostream.h>

template<class T>
void Insert(T a[], int n, const T& x)
{// Insert x into the sorted array a[0:n-1].
   int i;
   for (i = n-1; i >= 0 && x < a[i]; i--)
      a[i+1] = a[i];
   a[i+1] = x;
}

template<class T>
void InsertionSort(T a[], int n)
{// Sort a[0:n-1].
   for (int i = 1; i < n; i++) {
      T t = a[i];
      Insert(a, i, t);
      }
}

void main(void)
{
   int y[10] = {10,7,8,9,4, 2, 3, 6, 5,1};
   InsertionSort(y,10);
   for (int i=0; i< 10; i++)
      cout << y[i] << ' ';
}
