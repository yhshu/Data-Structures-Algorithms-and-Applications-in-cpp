
// recursive dynamic programming image compression
// nonrecursive traceback

#include <iostream.h>

int L = 256, header = 11;
int kay[6];
int l[6] = {0, 6, 3, 10, 2, 3};
int b[6] = {0, 1, 2, 3, 2, 1};
int n = 5;

int S(int i)
{// Return S(i) and compute kay[i].
   if (i == 0) return 0;
   // compute min term of Eq. 15.3 for k = 1
   int lsum = l[i], bmax = b[i];
   int s = S(i-1) + lsum * bmax;
   kay[i] = 1;

   // compute min term for remaining k and find min
   for (int k = 2; k <= i && lsum+l[i-k+1] <= L; k++) {
      lsum += l[i-k+1];
      if (bmax < b[i-k+1]) bmax = b[i-k+1];
      int t = S(i-k);     
      if (s > t + lsum * bmax) {
         s = t + lsum * bmax;
         kay[i] = k;}
      }

   return s + header;
}   

void Traceback(int kay[], int n)
{// Decompose into segments.
   while (n > 0) {
      cout << "New segment begins at "
           << (n - kay[n] + 1) << endl;
      n -= kay[n];
      }
}

void main(void)
{
   cout << "Minimum length is " << S(n) << endl;
   cout << "kay values are" << endl;
   for (int i = 1; i <= n; i++)
      cout << kay[i] << ' ';
   cout << endl;
   Traceback(kay,n);
}
