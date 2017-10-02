
// sum n numbers
#include<iostream>
#include<algorithm> // has copy

using namespace std;

template<class T>
T sum(T a[], int n)
{// Return sum of the numbers a[0:n-1].
   T theSum = 0;
   for (int i = 0; i < n; i++)
      theSum += a[i];
   return theSum;
}

int main()
{
   int a[6] = {1, 2, 3, 4, 5, 6};

   // output the array elements
   cout << "a[0:5] = ";
   copy(a, a+6, ostream_iterator<int>(cout, " "));
   cout << endl;

   // test the function sum
   cout << "sum(a,0) = " << sum(a,0) << endl;
   cout << "sum(a,1) = " << sum(a,1) << endl;
   cout << "sum(a,6) = " << sum(a,6) << endl;
   return 0;
}
