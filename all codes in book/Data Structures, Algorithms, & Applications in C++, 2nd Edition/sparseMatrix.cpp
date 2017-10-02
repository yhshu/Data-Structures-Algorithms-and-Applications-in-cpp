// test array based sparse matrix class

#include <iostream>
#include "sparseMatrix.h"

int main(void)
{
   sparseMatrix<int> a, b, c;

   // test input and output
   cin >> a;
   cout << "Matrix a is" << endl << a;
   cin >> b;
   cout << "Matrix b is" << endl << b;

   // test transpose
   a.transpose(c);
   cout << "The transpose of a is" << endl << c;

   // test add
   a.add(b,c);
   cout << "The sum of a and b is" << endl << c;

   return 0;
}
