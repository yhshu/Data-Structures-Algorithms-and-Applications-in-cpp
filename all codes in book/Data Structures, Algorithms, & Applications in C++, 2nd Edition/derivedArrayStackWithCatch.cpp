// test derivedArrayStackWithCatch

#include <iostream>
#include "derivedArrayStackWithCatch.h"
#include "myExceptions.h"

using namespace std;

int main(void)
{
   derivedArrayStackWithCatch<int> s;

   // add a few elements
   s.push(1);
   s.push(2);
   s.push(3);
   s.push(4);

   cout << "Stack should be 1234, bottom to top" << endl;

   // test empty and size
   if (s.empty())
      cout << "The stack is empty" << endl;
   else
      cout << "The stack is not empty" << endl;

   cout << "The stack size is " << s.size() << endl;

   while (!s.empty())
   {
      cout << "Stack top is " << s.top() << endl;
      s.pop();
      cout << "Popped top element" << endl;
   }

   try {s.pop();}
   catch (stackEmpty message)
   {
      cout << "Last pop failed " << endl;
      message.outputMessage();
   }

   return 0;
}
