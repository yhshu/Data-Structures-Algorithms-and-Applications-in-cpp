// insertion sort

#include <iostream>
#include <algorithm> // has copy

using namespace std;


template<class T>
void insert(T a[], int n, const T& x)
{// Insert x into the sorted array a[0:n-1].
   int i;
   for (i = n-1; i >= 0 && x < a[i]; i--)
      a[i+1] = a[i];
   a[i+1] = x;
}

template<class T>
void insertionSort(T a[], int n)
{// Sort a[0:n-1] using the insertion sort method.
   for (int i = 1; i < n; i++)
   {
      T t = a[i];
      insert(a, i, t);
   }
}

int main()
{
   int a[10] = {3, 2, 4, 1, 6, 9, 8, 7, 5, 0};

   // output the elements
   cout << "a[0:9] = ";
   copy(a, a+10, ostream_iterator<int>(cout, " "));
   cout << endl;

   // sort
   insertionSort(a,10);

   // output the sorted sequence
   cout << "After the sort, a[0:9] = ";
   copy(a, a+10, ostream_iterator<int>(cout, " "));
   cout << endl;
   return 0;
}
