// evaluate a polynomial

#include <iostream.h>

template<class T>
T PolyEval(T coeff[], int n, const T& x)
{// Evaluate the degree n polynomial with
 // coefficients coeff[0:n] at the point x.
   T y = 1, value = coeff[0];
   for (int i = 1; i <= n; i++) {
      // add in next term
      y *= x;
      value += y * coeff[i];
      }
   return value;
}

void main(void)
{
   int a[6] = {1, 2, 3, 4, 5, 6};
   cout << PolyEval(a,5,2) << endl;
}
