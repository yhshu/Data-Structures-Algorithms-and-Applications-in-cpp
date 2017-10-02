

// test  circular list polynomial class

#include <iostream.h>
#include "poly2.h"

void main(void)
{
   CPolynomial<int> A, B, C;
   cin >> A;
   cout << "Polynomial A is" << endl << A;

   // polynomial with smaller degree than A
   cin >> B;
   cout << "Polynomial B is" << endl << B;
   cout << "A + B =" << endl << (A + B);
   cout << "A - B =" << endl << (A - B);
   cout << "A * B =" << endl << (A * B);
   cout << "A / B =" << endl << (A / B);

   // polynomial with higher degree than A
   cin >> B;
   cout << "Polynomial B is" << endl << B;
   cout << "A + B =" << endl << (A + B);
   cout << "A - B =" << endl << (A - B);
   cout << "A * B =" << endl << (A * B);
   cout << "A / B =" << endl << (A / B);

   // polynomial with same degree as A
   cin >> C;
   cout << "Polynomial A is" << endl << A;
   cout << "Polynomial B is" << endl << B;
   cout << "Polynomial C is" << endl << C;
   cout << "A + C =" << endl << (A + C);
   cout << "A - C =" << endl << (A - C);
   cout << "A * C =" << endl << (A * C);
   cout << "A / C =" << endl << (A / C);
   cout << "A + B + C =" << endl << (A + B + C);

   // A is zero
   cin >> A;
   cout << "Polynomial A is" << endl << A;
   cout << "Polynomial C is" << endl << C;
   cout << "A + C =" << endl << (A + C);
   cout << "A - C =" << endl << (A - C);
   cout << "A * C =" << endl << (A * C);
   
   // multiply and divide by 1
   cin >> A;
   cout << "Polynomial A is" << endl << A;
   cout << "Polynomial C is" << endl << C;
   cout << "A * C =" << endl << (A * C);
   cout << "A / C =" << endl << (A / C);
   
   // another two multiplies and  divides
   for (int i = 1; i <= 2; i++) {
      cin >> A;
      cout << "Polynomial A is" << endl << A;
      cin >> C;
      cout << "Polynomial C is" << endl << C;
      cout << "A * C =" << endl << (A * C);
      cout << "A / C =" << endl << (A / C);
      }

   // do three evaluations
   cout << "A(0) = " << A(0) << endl;
   cout << "A(1) = " << A(1) << endl;
   cout << "A(2) = " << A(2) << endl;


}
