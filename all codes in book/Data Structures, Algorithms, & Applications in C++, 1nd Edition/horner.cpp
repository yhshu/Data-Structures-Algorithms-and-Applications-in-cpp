// evaluate a polynomial using Horner's rule

#include <iostream.h>

template<class T>
T Horner(T coeff[], int n, const T& x)
{// Evaluate the degree n polynomial with
 // coefficients coeff[0:n] at the point x.
   T value = coeff[n];
   for (int i = 1; i <= n; i++)
      value = value * x + coeff[n - i];
   return value;
}

void main(void)
{
   int a[6] = {1, 2, 3, 4, 5, 6};
   cout << Horner(a,5,2) << endl;
}
