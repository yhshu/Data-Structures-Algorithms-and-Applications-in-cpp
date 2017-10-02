// early terminating selection sort

#include <iostream>
#include <algorithm> // has copy

using namespace std;


template<class T>
void selectionSort(T a[], int n)
{// Early-terminating version of selection sort.
   bool sorted = false;
   for (int size = n; !sorted && (size > 1); size--)
   {
      int indexOfMax = 0;
      sorted = true;
      // find largest
      for (int i = 1; i < size; i++)
         if (a[indexOfMax] <= a[i]) indexOfMax = i;
         else sorted = false; // out of order
      swap(a[indexOfMax], a[size - 1]);
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
   selectionSort(a,10);

   // output the sorted sequence
   cout << "After the sort, a[0:9] = ";
   copy(a, a+10, ostream_iterator<int>(cout, " "));
   cout << endl;
   return 0;
}
