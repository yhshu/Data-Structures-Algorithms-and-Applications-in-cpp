// test max height biased leftist tree class

#include <iostream>
#include "maxhblt.h"

using namespace std;

int main(void)
{
   maxHblt<int> h, j;
   int a[6] = {0, 7, 9, 1, 8, 11};
   h.initialize(a,5);
   cout << "One tree in postorder is" << endl;
   cout << "Tree size is " << h.size() << endl;
   h.output();
   int b[5] = {0, 2, 6, 4, 9};

   j.initialize(b,4);
   cout << "Other tree in postorder is" << endl;
   cout << "Tree size is " << j.size() << endl;
   j.output();

   h.meld(j);
   cout << "After melding, the tree in postorder is" << endl;
   cout << "Tree size is " << h.size() << endl;
   h.output();

   int w = h.top();
   h.pop();
   int x = h.top();
   h.pop();
   int y = h.top();
   h.pop();
   int z = h.top();
   h.pop();
   cout << "After popping four elements, the tree is" << endl;
   cout << "Tree size is " << h.size() << endl;
   h.output();
   cout << "The popped elements, in order, are" << endl;
   cout << w << "  " << x << "  " << y << "  " << z << endl;

   h.push(10);
   h.push(20);
   h.push(5);
   cout << "After pushing 10, 20 & 5, the tree is" << endl;
   cout << "Leftist tree in postorder" << endl;
   cout << "Tree size is " << h.size() << endl;
   h.output();

   h.push(15);
   h.push(30);
   h.push(2);
   cout << "After pushing 15, 30 & 15, the tree is" << endl;
   cout << "Leftist tree in postorder" << endl;
   cout << "Tree size is " << h.size() << endl;
   h.output();

   cout << "The max element is " << h.top() << endl;

   h.pop();
   cout << "Popped max element " << endl;
   cout << "Leftist tree in postorder" << endl;
   cout << "Tree size is " << h.size() << endl;
   h.output();

   x = h.top();
   h.pop();
   cout << "Popped max element " << x << endl;
   cout << "Tree size is " << h.size() << endl;
   cout << "Leftist tree in postorder" << endl;
   h.output();

   while (true)
   {// empty out
      try
      {
         x = h.top();
         h.pop();
         cout << "Popped " << x << endl;
         cout << "Tree size is " << h.size() << endl;
      }
      catch (queueEmpty) {break;}
   }

   return 0;
}
