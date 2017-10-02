
#include<iostream.h>
#include "astack.h"
void main(void)
{
   try {
      Stack<int> S(9);
      cin >> S;
      cout << "Stack size is "
           << S.Size() << endl;
      cout << S << endl;
      }
   catch (...) {
      cerr << "An exception has occurred"
           << endl;
      }
}
