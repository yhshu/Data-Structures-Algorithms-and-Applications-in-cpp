
// multiply n numbers using the STL algorithm accumulate and
// the STL functor multiplies
#include <iostream>
#include <algorithm>     // has copy
#include <numeric>       // has accumulate
#include <functional>    // has multiplies

using namespace std;

template<class T>
T product(T a[], int n)
{// Return sum of the numbers a[0:n-1].
   T theProduct = 1;
   return accumulate(a, a+n, theProduct, multiplies<T>());
}

int main()
{
   int a[6] = {1, 2, 3, 4, 5, 6};

   // output the array elements
   cout << "a[0:5] = ";
   copy(a, a+6, ostream_iterator<int>(cout, " "));
   cout << endl;

   // test the function product
   cout << "product(a,0) = " << product(a,0) << endl;
   cout << "product(a,1) = " << product(a,1) << endl;
   cout << "product(a,6) = " << product(a,6) << endl;
   return 0;
}
