

// nonrecursive code to compute a Fibonacci number

#include <iostream.h>

int Fibonacci(int n)
{// Return the n'th Fibonacci number, n >= 0

   if (n == 0) return 0;
   if (n == 1) return 1;
   int SecondLast = 0;  // second last Fibonacci number
                        // computed so far
   int Last = 1;        // last Fibonacci number
                        // computed so far
   // compute new numbers
   for (int i = 2; i <= n; i++) {
      // compute i'th Fibonacci number
      int Next = Last + SecondLast;
      // update Last and SecondLast
      SecondLast = Last;
      Last = Next;
      }

   return Last;
}

void main(void)
{
   cout << "The 2nd Fibonacci number is "
        << Fibonacci(2) << endl;

   cout << "The 3rd Fibonacci number is "
        << Fibonacci(3) << endl;

   cout << "The 4th Fibonacci number is "
        << Fibonacci(4) << endl;

   cout << "The 5th Fibonacci number is "
        << Fibonacci(5) << endl;
}
