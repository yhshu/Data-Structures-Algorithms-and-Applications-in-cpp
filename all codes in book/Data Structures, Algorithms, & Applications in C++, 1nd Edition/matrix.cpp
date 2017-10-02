// test matrix class

#include <iostream.h>
#include "matrix.h"

void main(void)
{
   try {
      Matrix<int> X(3,2), Y, Z;
      int i, j;
      for (i = 1; i <= 3; i++)
         for (j = 1; j <= 2; j++)
            X(i,j) = 2*i + j;
      cout << "X(3,1) = " << X(3,1) << endl;
      cout << "X is" << endl;;
      cout << X << endl;
      Y = X;
      cout << "Y is" << endl;
      cout << Y << endl;
      X += 2;
      cout << "X incremented by 2 is" << endl;
      cout << X << endl;
      Z = Y + X;
      cout << "Y + X is" << endl;
      cout << Z << endl;
      cout << "-(Y + X) is" << endl;
      cout << -Z << endl;
      Matrix<int> W(2,3);
      for (i = 1; i <= 2; i++)
         for (j = 1; j <= 3; j++)
            W(i,j) = i + j;
      cout << "W is" << endl;
      cout << W << endl;
      Z = Y * W;
      cout << "Y * W is" << endl;
      cout << Z << endl;
      }
   catch (...) {
      cerr << "An exception has occurred" << endl;}
}
