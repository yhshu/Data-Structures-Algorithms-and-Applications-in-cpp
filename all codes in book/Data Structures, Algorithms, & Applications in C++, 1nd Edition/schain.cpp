// simulated chain

#include <iostream.h>
#include "schain.h"

SimSpace<int> SimChain<int>::S;

void main(void)
{
   int x;
   SimChain<int> c;
   cout << "Chain length is " << c.Length() << endl;
   c.Insert(0,2).Insert(1,6);
   cout << "Chain length is " << c.Length() << endl;
   c.Find(1,x);
   cout <<"First element is " << x << endl;
   c.Delete(1,x);
   cout << "Deleted " << x << endl;
   cout << "New length is " << c.Length() << endl;
   cout << "Position of 2 is " << c.Search(2) << endl;
   cout << "Position of 6 is " << c.Search(6) << endl;
   c.Insert(0,9).Insert(1,8).Insert(2,7);
   cout << "Current chain is " << c << endl;
   cout << "Its length is " << c.Length() << endl;
}
