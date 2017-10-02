// test 2D array class

#include <iostream.h>
#include "array2d.h"

void main(void)
{
   try {
      int i, j;
      Array2D<int> X(3,2), Y, Z;
      for (i = 0; i < 3; i++)
         for (j = 0; j < 2; j++)
            X[i][j] = 2*i + j;
      cout << "X[2][1] = " << X[2][1] << endl;
      cout << "X is" << endl;
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
      Array2D<int> W(2,3);
      for (i = 0; i < 2; i++)
         for (j = 0; j < 3; j++)
            W[i][j] = i + j;
      cout << "W is" << endl;
      cout << W << endl;
      Z = Y * W;
      cout << "Y * W is" << endl;
      cout << Z << endl;
      }
   catch (...) {
      cerr << "An exception has occurred" << endl;}
}
