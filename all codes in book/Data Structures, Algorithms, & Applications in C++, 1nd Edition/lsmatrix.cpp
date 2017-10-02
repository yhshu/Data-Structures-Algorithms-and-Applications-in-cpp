// test linked sparse matrix class

#include <iostream.h>
#include "lsmatrix.h"

void main(void)
{
   LinkedMatrix<int> A, B, C;
   cin >> A;
   cout << "Matrix A is" << endl << A;
   cin >> B;
   cout << "Matrix B is" << endl << B;
   A.Transpose(C);
   cout << "The transpose of A is" << endl << C;
}
