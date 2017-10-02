// test linked sparse matrix class

#include <iostream>
#include "linkedMatrix.h"

using namespace std;

int main(void)
{
   linkedMatrix<int> a, b, c;

   // test input and output
   cin >> a;
   cout << "Matrix a is" << endl << a;
   cin >> b;
   cout << "Matrix b is" << endl << b;

   // test transpose
   a.transpose(c);
   cout << "The transpose of a is" << endl << c;

   return 0;
}
