// match parentheses

#include <iostream>
#include <string>
#include "arrayStack.h"

using namespace std;


void printMatchedPairs(string expr)
{// Parenthesis matching.
   arrayStack<int> s;
   int length = (int) expr.size();

   // scan expression expr for ( and )
   for (int i = 0; i < length; i++)
      if (expr.at(i) == '(') 
         s.push(i);
      else
         if (expr.at(i) == ')')
   	 try
         {// remove location of matching '(' from stack
            cout << s.top() << ' ' << i << endl;
            s.pop();  // unstack match
         }
         catch (stackEmpty)
         {// stack was empty, no match exists
            cout << "No match for right parenthesis"
                 << " at " << i << endl;
         }

   // remaining '(' in stack are unmatched
   while (!s.empty()) 
   {
      cout << "No match for left parenthesis at "
           << s.top() << endl;
      s.pop();
   }
}

int main(void)
{
   string expr;
   cout << "Type an expression" << endl;
   cin >> expr;
   cout <<"The pairs of matching parentheses in"
        << endl << expr << endl << "are" << endl;

   printMatchedPairs(expr);

   return 0;
}
