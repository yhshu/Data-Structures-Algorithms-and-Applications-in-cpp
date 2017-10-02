// offline equivalence classes problem 


#include <iostream>
#include "arrayStack.h"

using namespace std;

// input the relation pairs and output the classes 
int main()
{
   int n,   // number of elements
       r;   // number of relations

   cout << "Enter number of elements" << endl;
   cin >> n;
   if (n < 2)
   {
      cout << "Too few elements" << endl;
      return 1;   // terminate with error
   }

   cout << "Enter number of relations" << endl;
   cin >> r;
   if (r < 1)
   {
      cout << "Too few relations" << endl;
      return 1;   // terminate with error
   }

   // create an array of empty stacks, stack[0] not used
   arrayStack<int>* list = new arrayStack<int> [n+1];
               
   // input the r relations and put on lists
   int a, b;  // (a, b) is a relation
   for (int i = 1; i <= r; i++)
   {
       cout << "Enter next relation/pair" << endl;
       cin >> a >> b;
       list[a].push(b);
       list[b].push(a);
   }
   
   // initialize to output equivalence classes
   arrayStack<int> unprocessedList;
   bool* out = new bool[n + 1];
   for (int i = 1; i <= n; i++)
      out[i] = false;

   // output equivalence classes
   for (int i = 1; i <= n; i++)
     if (!out[i])
     {// start of a new class
         cout << "Next class is: " << i << " ";
         out[i] = true;
         unprocessedList.push(i);
         // get rest of class from unprocessedList
         while (!unprocessedList.empty())
         {
            int j = unprocessedList.top();
            unprocessedList.pop();
 
            // elements on list[j] are in the same class
            while (!list[j].empty())
            {
               int q = list[j].top();
               list[j].pop();
               if (!out[q])  // q not yet output
               {
                   cout << q << " ";
                   out[q] = true;
                   unprocessedList.push(q);
               }
            }
         }
         cout << endl;
      }

   cout << "End of list of equivalence classes" << endl;

   return 0;
}
