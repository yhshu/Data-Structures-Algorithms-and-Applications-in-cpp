// insert into a sorted array

#include <iostream.h>

template<class T>
void Insert(T a[], int& n, const T& x)
{// Insert x into the sorted array a[0:n-1].
 // Assume a is of size > n 
   int i;
   for (i = n-1; i >= 0 && x < a[i]; i--)
      a[i+1] = a[i];
   a[i+1] = x;
   n++; // one element added to a
}

void main(void)
{
   int y[15] = {1,2,3,4,5,6,7,8,9,10,0,0,0,0,0};
   int n = 10;
   int x = 0;
   Insert(y,n,x);
   for (int i=0; i<n; i++)
      cout << y[i] << ' ';
}
