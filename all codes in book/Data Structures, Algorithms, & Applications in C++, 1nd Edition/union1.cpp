// simple union/find using 1D array

#include <iostream.h>
#include "xcept.h"

int *E, n;

void Initialize(int n)
{// Initialize n classes with one element each.
   E = new int [n + 1];
   for (int e = 1; e <= n; e++)
      E[e] = e;
}

void Union(int i, int j)
{// Union the classes i and j.
   for (int k = 1; k <= n; k++)
      if (E[k] == j) E[k] = i;
}

int Find(int e)
{// Find the class that contains element i.
   return E[e];
}

void main(void)
{
   n = 10;
   Initialize(n);
   Union(1,2);
   Union(3,4);
   Union(1,3);
   cout << '1' << ' ' << Find(1) << ' ' << '2' << ' ' << Find(2) << endl;
   cout << '3' << ' ' << Find(3) << ' ' << '4' << ' ' << Find(4) << endl;
   cout << '5' << ' ' << Find(5) << ' ' << '6' << ' ' << Find(6) << endl;
}
