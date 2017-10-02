// find the roots of a quadratic

#include <iostream.h>
#include <stdlib.h>  // has exit function
#include <math.h>    // has sqrt function

template<class T>
void InputCoefficients(T& a, T& b, T& c)
{// Read in the coefficients of the quadratic.

   cout << "Enter the coefficients a, b, and c"
        << endl
        << "a should not be zero"
        << endl;
   cin >> a >> b >> c;
   if (a == 0) {cout << "Bad input. "
                     << "a is zero." << endl;
                exit(1);}
}

template<class T>
void OutputRoots(T a, T b, T c)
{// Compute and output the roots of the quadratic.

   T d = b*b-4*a*c;
   if (d > 0) {// two real roots
               float sqrtd = sqrt(d);
               cout << "There are two real roots "
                    << (-b+sqrtd)/(2*a) << " and "
                    << (-b-sqrtd)/(2*a)
                    << endl;}
   else if (d == 0)
           // both roots are the same
           cout << "There is only one distinct root "
                << -b/(2*a)
                << endl;
        else //  complex conjugate roots
             cout << "The roots are complex"
                  << endl
                  << "The real part is "
                  << -b/(2*a) << endl
                  << "The imaginary part is "
                  << sqrt(-d)/(2*a) << endl;
   }
   
void main(void)
{
   int a, b, c;
   for (int i = 1; i <= 4; i++) {
      InputCoefficients(a,b,c);
      OutputRoots(a,b,c);}
}
