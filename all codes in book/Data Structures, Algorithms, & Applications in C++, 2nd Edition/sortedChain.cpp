// test sorted chain class
#include<iostream>
#include "sortedChain.h"

using namespace std;

void main()
{
   sortedChain<int, int> z;
   pair<int, int> p;

   // test insert
   p.first = 2; p.second = 10;
   z.insert(p);
   p.first = 10; p.second = 50;
   z.insert(p);
   p.first = 6; p.second = 30;
   z.insert(p);
   p.first = 8; p.second = 40;
   z.insert(p);
   p.first = 1; p.second = 5;
   z.insert(p);
   p.first = 12; p.second = 60;
   z.insert(p);
   cout << "The chain is " << z << endl;
   cout << "Its size is " << z.size() << endl;

   // test find
   cout << "Element associated with 1 is " << z.find(1)->second << endl;
   cout << "Element associated with 6 is " << z.find(6)->second << endl;
   cout << "Element associated with 12 is " << z.find(12)->second << endl;

   // test erase
   z.erase(1);
   z.erase(2);
   z.erase(6);
   z.erase(12);
   cout << "Deleted 1, 2, 6, 12" << endl;
   cout << "The chain is " << z << endl;
   cout << "Its size is " << z.size() << endl;
}
