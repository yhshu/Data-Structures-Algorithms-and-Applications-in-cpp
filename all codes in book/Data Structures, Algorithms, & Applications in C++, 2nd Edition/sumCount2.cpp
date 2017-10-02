// simplified step count of sum of n numbers

#include <iostream>
#include <algorithm> // has copy

using namespace std;


int stepCount = 0;

template<class T>
T sum(T a[], int n)
{// Return sum of numbers a[0:n - 1].
   for (int i = 0; i < n; i++)
      stepCount += 2;
   stepCount += 3; 
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
   sum(a,0);
   cout << "For sum(a,0) the step count is " << stepCount << endl;
   stepCount = 0;
   sum(a,1);
   cout << "For sum(a,1) the step count is " << stepCount << endl;
   stepCount = 0;
   sum(a,6);
   cout << "For sum(a,6) the step count is " << stepCount << endl;
   return 0;
}
