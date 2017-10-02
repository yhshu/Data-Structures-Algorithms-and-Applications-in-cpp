// divide and conquer function to find the index/location of the
// minimum and maximum elements in array a

#include <iostream>
#include <iterator>

using namespace std;

template<class T>
bool minmax(T a[], int n, int& indexOfMin, int& indexOfMax)
{// Locate min and max elements in a[0:n-1].
 // Return false if less than one element.
   if (n < 1) return false;

   if (n == 1)
   {
      indexOfMin = indexOfMax = 0;
      return true;
   }

   // n > 1
   int s = 1;              // start point for loop
   if (n % 2 == 1)  // n is odd
      indexOfMin = indexOfMax = 0;
   else
   {// n is even, compare first pair
      if (a[0] > a[1])
      {
         indexOfMin = 1;
         indexOfMax = 0;
      }
      else
      {
         indexOfMin = 0;
         indexOfMax = 1;
      }
      s = 2;
   }

   // compare remaining pairs
   for (int i = s; i < n; i += 2)
   {
      // find larger of a[i] and a[i + 1], then compare larger one
      // with a[p.second] and smaller one with a[p.first]
      if (a[i] > a[i + 1])
      {
         if (a[i] > a[indexOfMax])
            indexOfMax = i;
         if (a[i + 1] < a[indexOfMin])
            indexOfMin = i + 1;
      }
      else
      {
         if (a[i + 1] > a[indexOfMax])
            indexOfMax = i + 1;
         if (a[i] < a[indexOfMin])
            indexOfMin = i;
      }
   }

   return true;
}

int main()
{
   int a[] = {3, 2, 4, 1, 6, 9, 8, 7, 5, 0};
   int n = 10, theMin, theMax;

   // output the array elements
   cout << "a[0:9] = ";
   copy(a, a + n, ostream_iterator<int>(cout, " "));
   cout << endl;

   // locate min and max
   minmax(a, n, theMin, theMax);

   // output locations and values
   cout << "The min element is at " << theMin  << endl
        << "Its value is " << a[theMin] << endl;
   cout << "The max element is at " << theMax  << endl
        << "Its value is " << a[theMax] << endl;
   return 0;
}
