

#include<iostream.h>
#include "bqueue.h"
void main(void)
{
   try {
      Queue<int> A(9), B(9), C(18), D(9);
      cin >> A;
      cout << A << endl;
      A.Split(B,C);
      cout << "The split queues are " << endl
           << B << endl
           << C << endl;

      cout << "After combining, we get " << endl
           << D.Combine(B,C) << endl;

      cin >> B;
      C.Combine(A,B);
      cout << "Two queues and their combination are"
           << endl
           << A << endl
           << B << endl
           << C << endl;
      }
   catch (...) {
      cerr << "An exception has occurred"
           << endl;
      }
}
