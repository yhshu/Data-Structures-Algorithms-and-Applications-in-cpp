// file insort.h
//insertion sort

#ifndef InsertionSort_
#define InsertionSort_

template<class T>
void InsertionSort(T a[], int n)
{// Sort a[0:n-1].
   for (int i = 1; i < n; i++) {
      // insert a[i] into a[0:i-1]
      T t = a[i];
      int j;
      for (j = i-1; j >= 0 && t < a[j]; j--)
         a[j+1] = a[j];
      a[j+1] = t;}
}

#endif
