// greedy container loading

#include <iostream.h>

void IndirectSort(int w[], int t[], int n)
{// Cluge to test when weights already in order.
   for (int i=1; i <= n; i++) t[i] = i;
}

template<class T>
void ContainerLoading(int x[],  T w[], T c, int n)
{// Greedy algorithm for container loading.
 // Set x[i] = 1 iff container i, 1<=i<=n is loaded.
 // c is ship capacity, w gives container weights.

   // do indirect addressing sort of weights
   // t is the indirect addressing table
   int *t = new int [n+1];
   IndirectSort(w, t, n);
   // now, w[t[i]] <= w[t[i+1]], 1<=i<n
   
   // initialize x
   for (int i = 1; i <= n; i++)
      x[i] = 0;
   
   // select objects in order of weight
   for (i = 1; i <= n && w[t[i]] <= c; i++) {
      x[t[i]] = 1;
      c -= w[t[i]];}  // remaining capacity
   
   delete [] t;
}

void main(void)
{
   int w[9] = {0, 20, 50, 50, 80, 90, 100, 150, 200}, x[9];
   ContainerLoading(x, w, 400, 8);
   cout << "Loading vector is" << endl;
   for (int i = 1; i <= 8; i++)
      cout << x[i] << ' ';
   cout << endl;
}
