// find the roots of a quadratic

#include <iostream>
#include <math.h>    // has sqrt function
#include "myExceptions.h"

using namespace std;

void inputCoefficients(double& a, double& b, double& c)
{// Read in the coefficients of the quadratic.

   cout << "Enter the coefficients a, b, and c"
        << endl
        << "a should not be zero"
        << endl;
   cin >> a >> b >> c;
   if (fabs(a) <= 0.1E-9) 
       throw illegalInputData("a should be non-zero");
}

void outputRoots(const double& a, const double& b, const double& c)
{// Compute and output the roots of the quadratic.

   double d = b * b - 4 * a * c;
   if (d > 0) {// two real roots
                 double sqrtd = sqrt(d);
                 cout << "There are two real roots "
                      << (-b + sqrtd) / (2 * a) << " and "
                      << (-b - sqrtd) / (2 * a)
                      << endl;
               }
   else if (d == 0)
           // both roots are the same
           cout << "There is only one distinct root "
                << -b / (2 * a)
                << endl;
        else //  complex conjugate roots
             cout << "The roots are complex"
                  << endl
                  << "The real part is "
                  << -b / (2 * a) << endl
                  << "The imaginary part is "
                  << sqrt(-d) / (2 * a) << endl;
}
   
int main()
{
   double a, b, c;

   // test with 4 sets of coefficients
   for (int i = 1; i <= 4; i++) {
      try {
         inputCoefficients(a,b,c);
          }
      catch (illegalInputData e) {
         cout << "Caught illegalInputData exception" << endl;
         e.outputMessage();
         return 1;
          }
     
      cout << "The coefficients of the quadratic are "
           << a << " " << b << " " << c << endl;
      outputRoots(a,b,c);
      cout << endl;}
   return 0;
}

