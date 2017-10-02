
// compute n!

#include <iostream.h>

int Factorial(int n)
{// Compute n!
   if (n <= 1) return 1;
   else return n * Factorial(n - 1);
}

void main(void)
{
   cout << "5! = " << Factorial(5) << endl;
}
