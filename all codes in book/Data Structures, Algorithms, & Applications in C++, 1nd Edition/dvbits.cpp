// dynamic programming image compression
// non-recursive version

#include <iostream.h>

void Vbits(int l[], int b[], int n, int s[], int kay[])
{// Compute s[i] and kay[i] for all i.
   int L = 256, header = 11;
   s[0] = 0;
   // compute s[i] using Eq. 15.3
   for (int i = 1; i <= n; i++) {
      // compute min term for k = 1
      int lsum = l[i],
          bmax = b[i];
      s[i] = s[i - 1] + lsum * bmax;
      kay[i] = 1;

      // compute for remaining k and update
      for (int k = 2; k <= i && lsum+l[i-k+1] <= L; k++) {
         lsum += l[i-k+1];
         if (bmax < b[i-k+1]) bmax = b[i-k+1];
         if (s[i] > s[i-k] + lsum * bmax) {
               s[i] = s[i-k] + lsum * bmax;
               kay[i] = k;}
         }

      s[i] += header;
      }
}

void Traceback(int kay[], int n)
{// Decompose into segments.
   if (n == 0) return;
   Traceback(kay, n-kay[n]);
   cout << "New segment begins at " << (n - kay[n] + 1) << endl;
}

void main(void)
{
   int l[6] = {0, 6, 3, 10, 2, 3};
   int b[6] = {0, 1, 2, 3, 2, 1};
   int s[6], kay[6];
   int n = 5;
   Vbits(l,b,n,s,kay);
   
   cout << "s values are" << endl;
   for (int i = 1; i <= n; i++)
      cout << s[i] << ' ';
   cout << endl;

   cout << "kay values are" << endl;
   for (i = 1; i <= n; i++) 
     cout << kay[i] << ' ';
   cout << endl;
   
   Traceback(kay,n);
}
