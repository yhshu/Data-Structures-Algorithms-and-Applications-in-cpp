


// test tridiagonal matrix class

#include <iostream.h>
#include "tridiag.h"

void main(void)
{
   try {
      TridiagonalMatrix<int> X, Y, Z;
      cin >> X;
      cout << "X is " << endl
           << X << endl;
      Y = X;
      cout << "Y is " << endl
           << Y << endl;
      X += 2;
      cout << "X incremented by 2 is "
           << endl << X << endl;
      Z = Y + X;
      cout << "Y + X is " 
           << endl << Z << endl;
      cout << "-(Y + X) is " 
           << endl << -Z << endl;
      cout << "X transpose is " 
           << endl << X.Transpose() << endl;
      }
   catch (...) {
      cerr << "An exception has occurred" << endl;}
}
