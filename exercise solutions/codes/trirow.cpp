
// test TriByRows matrix class

#include<iostream.h>
#include<stdlib.h>
#include "trirow.h"

void main(void)
{
   try {
      TriByRows<int> A(20);
      A.Store(22,1,1).Store(44,5,5);
      A.Store(55,7,8).Store(0,8,5);
      cout << A.Retrieve(7,8) << endl;
      cout << A.Retrieve(5,5) << endl;
      cout << A.Retrieve(1,1) << endl;
      cout << A.Retrieve(10,1) << endl;
      cout << A.Retrieve(1,5) << endl;

      TriByRows<int> X, Y, Z;
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
