// insert into a sorted array

#include <iostream>
#include <algorithm> // has copy

using namespace std;


template<class T>
void insert(T a[], int& n, const T& x)
{// Insert x into the sorted array a[0:n-1].
 // Assume a is of size > n 
   int i;
   for (i = n-1; i >= 0 && x < a[i]; i--)
      a[i+1] = a[i];
   a[i+1] = x;
   n++; // one element added to a
}

int main()
{
   int a[10] = {1, 2, 4, 6, 8, 10, 12, 0, 0, 0};
   int x; // element to be inserted
   int n = 7;

   // output the elements
   cout << "a[0:6] = ";
   copy(a, a+n, ostream_iterator<int>(cout, " "));
   cout << endl;

   // do a few inserts
   x = 14;
   insert(a,n,x);
   cout << "After inserting 14, a[0:7] = ";
   copy(a, a+n, ostream_iterator<int>(cout, " "));
   cout << endl;

   x = 5;
   insert(a,n,x);
   cout << "After inserting 5, a[0:8] = ";
   copy(a, a+n, ostream_iterator<int>(cout, " "));
   cout << endl;

   x = 0;
   insert(a,n,x);
   cout << "After inserting 0, a[0:9] = ";
   copy(a, a+n, ostream_iterator<int>(cout, " "));
   cout << endl;

   return 0;
}
