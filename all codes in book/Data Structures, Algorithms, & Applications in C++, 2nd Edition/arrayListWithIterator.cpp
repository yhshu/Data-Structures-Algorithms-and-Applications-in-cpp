// test the iterator for arrayList
#include<iostream>
#include<algorithm>   // has reverse
#include<numeric>     // has accumulate
#include "linearList.h"
#include "arrayListWithIterator.h"

using namespace std;

int main()
{
   // create a linear list
   arrayList<int> y(2);
   y.insert(0, 2);
   y.insert(1, 6);
   y.insert(0, 1);
   y.insert(2, 4);
   y.insert(3, 5);
   y.insert(2, 3);
   cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
   cout << "Size of y = " << y.size() << endl;
   cout << "Capacity of y = " << y.capacity() << endl;

   // test iterator
   cout << "Ouput using forward iterators pre and post ++" << endl;
   for (arrayList<int>::iterator i = y.begin();
        i != y.end(); i++)
      cout << *i << "  ";
   cout << endl;
   for (arrayList<int>::iterator i = y.begin();
        i != y.end(); ++i)
      cout << *i << "  ";
   cout << endl;

   cout << "Ouput using backward iterators pre and post --" << endl;
   for (arrayList<int>::iterator i = y.end();
        i != y.begin(); cout << *(--i) << "  ");
   cout << endl;
   for (arrayList<int>::iterator i = y.end();
        i != y.begin();)
      {i--; cout << *i << "  "; *i += 1;} 
   cout << endl;
   cout << "Incremented by 1 list is " << y << endl;
   
   // try out some STL algorithms
   reverse(y.begin(), y.end());
   cout << "The reversed list is " << y << endl;
   int sum = accumulate(y.begin(), y.end(), 0);
   cout << "The sum of the elements is " << sum << endl;

   return 0;
}
