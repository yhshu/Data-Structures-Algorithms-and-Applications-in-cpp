// run time using class sparseMatrix as well as linkedMatrix

#include <iostream>
#include<time.h>
//#include "sparseMatrix.h"
#include "linkedMatrix.h"

using namespace std;

#pragma optimize("t", on)
int main()
{
   linkedMatrix<int> a, b, c;
//   sparseMatrix<int> a, b, c;
   int m = 20000;  // repetition factor
   int n = 500;   // matrix size


   cin >> a;
   cin >> b;

   long startTime = clock();
   for (int i = 1; i <= m; i++)
      a.transpose(b);
   double elapsedTime = ((double) (clock() - startTime)) / m;
   cout << "Transpose time for n = " << n << " is "
        << elapsedTime << " milliseconds" << endl;
   return 0;
}
