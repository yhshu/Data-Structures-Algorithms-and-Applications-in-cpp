
#include <iostream.h>

int factorial (int n)
{// Non-recursive program to compute n!
   if (n <= 1) return 1;
   int fact = 2;
   for (int i = 3; i <= n; i++)
      fact *= i;
   return fact;
}

void main()
{
   cout << factorial(4) << endl;
}
