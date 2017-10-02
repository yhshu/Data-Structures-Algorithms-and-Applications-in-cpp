// early terminating bubble sort

#include <iostream>
#include <algorithm> // has copy

using namespace std;


template<class T>
bool bubble(T a[], int n)
{// Bubble largest element in a[0:n-1] to right.
   bool swapped = false; // no swaps so far
   for (int i = 0; i < n - 1; i++)
      if (a[i] > a[i+1])
      {
         swap(a[i], a[i + 1]);
         swapped = true; // swap was done
      }
   return swapped;
}

template<class T>
void bubbleSort(T a[], int n)
{// Early-terminating version of bubble sort.
   for (int i = n; i > 1 && bubble(a, i); i--);
}

int main()
{
   int a[10] = {10,9,1,2,3,4,8,7,6,5};

   // output the elements
   cout << "a[0:9] = ";
   copy(a, a+10, ostream_iterator<int>(cout, " "));
   cout << endl;

   // sort
   bubbleSort(a,10);

   // output the sorted sequence
   cout << "After the sort, a[0:9] = ";
   copy(a, a+10, ostream_iterator<int>(cout, " "));
   cout << endl;
   return 0;
}
