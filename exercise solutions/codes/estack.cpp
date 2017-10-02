
#include<iostream.h>
#include "estack.h"
void main(void)
{
   LinkedStack<int> S;
   cin >> S;
   cout << S;
   cout << "The stack size is "
        << S.Size() << endl;
}
