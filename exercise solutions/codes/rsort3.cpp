
// rank or count sort

#include <iostream.h>

template<class T>
void Rearrange(T * &a, int n, int r[])
{// Rearrange the elements of a into sorted order
 // using an additional array u.
   T *u = new T [n+1];
   // move to correct place in u
   for (int i = 0; i < n; i++)
      u[r[i]] = a[i];

   // free space used by a[]
   delete [] a;

   // make a point to new space
   a = u;

}

template<class T>
void Rank(T a[], int n, int r[])
{// Rank the n elements a[0:n-1].
   for (int i = 0; i < n; i++)
      r[i] = 0;  // initialize
   // compare all element pairs
   for (i = 1; i < n; i++)
      for (int j = 0; j < i; j++)
         if (a[j] <= a[i]) r[i]++;
         else r[j]++;
}

void main(void)
{
   int *a;
   int r[6];
   a = new int [6];
   int n = 6;
   for (int i = 0; i < n; i++)
      a[i] = n - i;
   Rank(a,n,r);
   Rearrange(a,n,r);
   for (i = 0; i < n; i++)
      cout << a[i] << ' ';
   cout << endl;
}
