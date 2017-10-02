// dynamic programming recursive computation for image
// compression avoiding recomputations

#include <iostream.h>

int L = 256, header = 11;
int s[6] = {0,0,0,0,0,0}, kay[6];
int l[6] = {0, 6, 3, 10, 2, 3};
int b[6] = {0, 1, 2, 3, 2, 1};
int n = 5;

int S(int i)
{// Compute S(i) and kay[i].
 // Avoid recomputations.
   if (i == 0) return 0;
   if (s[i] > 0) return s[i]; // already computed
   // compute s[i]
   // first compute min term of Eq. 15.3 for k = 1
   int lsum = l[i], bmax = b[i];
   s[i] = S(i-1) + lsum * bmax;
   kay[i] = 1;

   // compute min term for remaining k and update
   for (int k = 2; k <= i && lsum+l[i-k+1] <= L; k++) {
      lsum += l[i-k+1];
      if (bmax < b[i-k+1]) bmax = b[i-k+1];
      int t = S(i-k); 
      if (s[i] > t + lsum * bmax) {
         s[i] = t + lsum * bmax;
         kay[i] = k;}
      }

   s[i] += header;
   return s[i];
}   

void Traceback(int kay[], int n)
{// Decompose into segments.
   if (n == 0) return;
   Traceback(kay, n-kay[n]);
   cout << "New segment begins at " << (n - kay[n] + 1) 
        << endl;
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
