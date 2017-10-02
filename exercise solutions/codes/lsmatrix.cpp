// test linked sparse matrix class

#include <iostream.h>
#include "lsmatrix.h"

void main(void)
{
   LinkedMatrix<int> A, B, C;
   cin >> A;
   cout << "Matrix A is" << endl << A;
   cout << "A(1,2) = " << A.Retrieve(1,2) << endl;
   cout << "A(1,4) = " << A.Retrieve(1,4) << endl;
   cout << "A(1,5) = " << A.Retrieve(1,5) << endl;
   cout << "A(2,2) = " << A.Retrieve(2,2) << endl;
   cout << "A(3,1) = " << A.Retrieve(3,1) << endl;
   cout << "A(4,3) = " << A.Retrieve(4,3) << endl;
   for (int i = 1; i <= 6; i++) {
      cout << "Enter row, col, and value of term to store"
           << endl;
      int row, col, value;
      cin >> row >> col >> value;
      A.Store(value, row, col);
      }
   cout << "The matrix is now" << endl << A;

   // input second matrix for add operation
   cin >> B;
   cout << "The second matrix is" << endl << B;
   A.Add(B,C);
   cout << "Their sum is" << endl << C;

  // lets try a subtraction
  cin >> A;
  cin >> B;
  cout << "The difference of the matrices" << endl << A;
  cout << "and" << endl << B;
  A.Subtract(B,C);
  cout << "is" << endl << C;
}
