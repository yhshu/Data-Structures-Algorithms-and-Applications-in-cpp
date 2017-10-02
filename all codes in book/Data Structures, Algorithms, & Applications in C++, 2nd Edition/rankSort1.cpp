// rank or count sort
// rearrange elements using an additioal array

#include <iostream>
#include <algorithm> // has copy

using namespace std;


template<class T>
void rearrange(T a[], int n, int r[])
{// Rearrange the elements of a into sorted order
 // using an additional array u.
   T *u = new T [n]; // create additional array

   // move to correct place in u
   for (int i = 0; i < n; i++)
      u[r[i]] = a[i];

   // move back to a
   for (i = 0; i < n; i++)
      a[i] = u[i];

   delete [] u;
}

template<class T>
void rank(T a[], int n, int r[])
{// Rank the n elements a[0:n-1].
 // Element ranks returned in r[0:n-1]
   for (int i = 0; i < n; i++)
      r[i] = 0;  // initialize

   // compare all element pairs
   for (int i = 1; i < n; i++)
      for (int j = 0; j < i; j++)
         if (a[j] <= a[i]) r[i]++;
         else r[j]++;
}

int main()
{
   int a[6] = {2, 6, 4, 3, 1, 5};
   int r[6];

   // output the elements
   cout << "a[0:5] = ";
   copy(a, a+6, ostream_iterator<int>(cout, " "));
   cout << endl;

   // sort
   rank(a,6,r);
   rearrange(a,6,r);

   // output the sorted sequence
   cout << "After the sort, a[0:5] = ";
   copy(a, a+6, ostream_iterator<int>(cout, " "));
   cout << endl;
   return 0;
}
