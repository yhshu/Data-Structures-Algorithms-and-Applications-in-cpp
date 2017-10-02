// ineffficient prefix sums

#include <iostream>
#include <algorithm>

using namespace std;

template <class T>
T sum(T a[], int n)
{// Return sum of numbers a[0:n - 1].
   T theSum = 0;
   for (int i = 0; i < n; i++)
      theSum += a[i];
   return theSum;
}

template <class T>
void inef(T a[], T b[], int n)
{// Compute prefix sums.
   for (int j = 0; j < n; j++)
      b[j] = sum(a, j + 1);
}

int main()
{
   int a[6] = {1, 2, 3, 4, 5, 6};
   int b[6];
   int n = 6;

   // output the array elements
   cout << "a[0:5] = ";
   copy(a, a+6, ostream_iterator<int>(cout, " "));
   cout << endl;

   // compute the prefix sums inefficiently
   inef(a,b,n);

   // output the prefix sums
   cout << "The prefix sums are ";
   copy(b, b+6, ostream_iterator<int>(cout, " "));
   cout << endl;
}
