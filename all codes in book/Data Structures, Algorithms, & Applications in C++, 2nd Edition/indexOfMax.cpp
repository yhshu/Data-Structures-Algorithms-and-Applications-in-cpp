// find location of maximum of n numbers

#include <iostream>
#include <algorithm> // has copy
#include "indexOfMax.h"

using namespace std;

int main()
{
   int a[6] = {1, 4, 2, 5, 6, 3};

   // output the array elements
   cout << "a[0:5] = ";
   copy(a, a+6, ostream_iterator<int>(cout, " "));
   cout << endl;

   // test the function indexOfMax
   cout << "max(a,1) = " << a[indexOfMax(a,1)] << endl;
   cout << "max(a,3) = " << a[indexOfMax(a,3)] << endl;
   cout << "max(a,6) = " << a[indexOfMax(a,6)] << endl;
   return 0;
}
