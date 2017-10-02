// step count for recursive sum of n numbers

#include <iostream>
#include <algorithm>

using namespace std;

int stepCount = 0;

template<class T>
T rSum(T a[], int n)
{// Return sum of numbers a[0:n - 1].
   stepCount++; // for if conditional
   if (n > 0) {stepCount++; // for return and rSum invocation
               return rSum(a, n-1) + a[n-1];}
   stepCount++; // for return
   return 0;
}

int main()
{
   int a[6] = {1, 2, 3, 4, 5, 6};

   // output the array elements
   cout << "a[0:5] = ";
   copy(a, a+6, ostream_iterator<int>(cout, " "));
   cout << endl;

   // determine the step count
   rSum(a,0);
   cout << "For rSum(a,0) the step count is " << stepCount << endl;
   stepCount = 0;
   rSum(a,1);
   cout << "For rSum(a,1) the step count is " << stepCount << endl;
   stepCount = 0;
   rSum(a,6);
   cout << "For rSum(a,6) the step count is " << stepCount << endl;
   return 0;
}
