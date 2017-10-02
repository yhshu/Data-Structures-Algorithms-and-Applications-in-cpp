// ineffficient prefix sums

#include <iostream.h>

int count = 0;

template <class T>
void Inef(T a[], T b[], int n)
{// Compute prefix sums.
   for (int j = 0; j < n; j++)
      count += 2 * j + 7;
   count++;
}


void main(void)
{
   int a[6] = {1, 2, 3, 4, 5, 6};
   int b[6];
   int n = 6;
   Inef(a,b,n);
   cout << "Step count is " << count << endl;
}
