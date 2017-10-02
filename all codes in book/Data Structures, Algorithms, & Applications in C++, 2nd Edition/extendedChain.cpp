// test extended chain
#include<iostream>
#include<numeric>     // has accumulate
#include "extendedChain.h"

using namespace std;

int main()
{
   // create an extended chain
   extendedChain<int> y;
   y.insert(0, 2);
   y.insert(1, 6);
   y.insert(0, 1);
   y.insert(2, 4);
   y.insert(3, 5);
   y.insert(2, 3);
   cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
   cout << "Size of y = " << y.size() << endl;

   // test iterator
   cout << "Ouput using forward iterators pre and post ++" << endl;
   for (extendedChain<int>::iterator i = y.begin();
        i != y.end(); i++)
      cout << *i << "  ";
   cout << endl;
   for (extendedChain<int>::iterator i = y.begin();
        i != y.end(); ++i)
   {
      cout << *i << "  ";
      *i += 1;
   }
   cout << endl;

   cout << "Incremented by 1 list is " << y << endl;
   
   // try out an STL algorithm
   int sum = accumulate(y.begin(), y.end(), 0);
   cout << "The sum of the elements is " << sum << endl;

   // clear the chain and do a few appends
   y.clear();
   y.push_back(1);
   y.push_back(2);
   y.push_back(3);
   cout << "Appended 3 integers, list y should be 1 2 3" << endl;
   cout << "Size of y = " << y.size() << endl;
   cout << y << endl;

   y.insert(3,4);
   y.insert(0,0);
   cout << "List y should be 0 1 2 3 4" << endl;
   cout << "Size of y = " << y.size() << endl;
   cout << y << endl;

   y.erase(4);
   y.erase(0);
   y.push_back(6);
   cout << "List y should be 1 2 3 6" << endl;
   cout << "Size of y = " << y.size() << endl;
   cout << y << endl;

   return 0;
}
