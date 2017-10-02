// sequential search of unordered list with an extra position

#include <iostream>
#include <algorithm>

using namespace std;

template<class T>
int sequentialSearch(T a[], int n, const T& x)
{// Search the unordered list a[0:n-1] for x.
 // Return position if found; return -1 otherwise.
   a[n] = x; // assume extra position available
   int i;
   for (i = 0; a[i] != x; i++);
   if (i == n) return -1;
   return i;
}

int main()
{
   int a[8] = {1, 5, 3, 4, 7, 2, 0, 0};
       // a[7]  is a free spot

   // output the array elements
   cout << "a[0:6] = ";
   copy(a, a+7, ostream_iterator<int>(cout, " "));
   cout << endl;

   // test the search function
   cout << "4 is at position " << sequentialSearch(a, 7, 4) << endl;
   cout << "0 is at position " << sequentialSearch(a, 7, 0) << endl;
   cout << "1 is at position " << sequentialSearch(a, 7, 1) << endl;
   cout << "8 is at position " << sequentialSearch(a, 7, 8) << endl;
   return 0;
}

