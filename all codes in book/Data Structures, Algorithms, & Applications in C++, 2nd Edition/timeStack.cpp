// run time for stack classes

#include <iostream>
#include<time.h>
//#include "arrayStack.h"
//#include "derivedArrayStack.h"
//#include "derivedArrayStackWithCatch.h"
#include "linkedStack.h"
//#include "derivedLinkedStack.h"
//#include <stack>

using namespace std;

//typedef arrayStack<int> stackType;
//typedef derivedArrayStack<int> stackType;
//typedef derivedArrayStackWithCatch<int> stackType;
typedef linkedStack<int> stackType;
//typedef derivedLinkedStack<int> stackType;
//typedef stack<int> stackType;

#pragma optimize("t", on)
int main()
{
//   stackType s(50000000);
     stackType s;
   int n = 10000000;  // number of push operations
   int x = 2;

   long startTime = clock();
   // push n elements
   for (int i = 1; i <= n; i++)
     s.push(x);

   // now pop them
   for (int i = 1; i <= n; i++)
   {
     s.top();
     s.pop();
   }
   long elapsedTime = clock() - startTime;
   cout << "Time for n = " << n << " stack operations is "
        << elapsedTime << " milliseconds" << endl;
   return 0;
}
