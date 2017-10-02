// test binary search tree with duplicates class

#include <iostream>
#include "dBinarySearchTree.h"

using namespace std;


int main(void)
{
   dBinarySearchTree<int, char> y;
   y.insert(pair<int, char>(1, 'a'));
   y.insert(pair<int, char>(6, 'f'));
   y.insert(pair<int, char>(3, 'c'));
   y.insert(pair<int, char>(4, 'e'));
   y.insert(pair<int, char>(1, 'b'));
   y.insert(pair<int, char>(6, 'g'));
   y.insert(pair<int, char>(3, 'd'));
   cout << "Tree size is " << y.size() << endl;
   cout << "Elements in ascending order are" << endl;
   y.ascend();

   pair<const int, char> *s = y.find(3);
   cout << "Search for 3 succeeds " << endl;
   cout << s->first << ' ' << s->second << endl;
   y.erase(3);
   cout << "3 deleted " << endl;
   cout << "Tree size is " << y.size() << endl;
   cout << "Elements in ascending order are" << endl;
   y.ascend();

   s = y.find(3);
   cout << "Search for 3 succeeds " << endl;
   cout << s->first << ' ' << s->second << endl;
   y.erase(3);
   cout << "3 deleted " << endl;
   cout << "Tree size is " << y.size() << endl;
   cout << "Elements in ascending order are" << endl;
   y.ascend();

   s = y.find(1);
   cout << "Search for 1 succeeds " << endl;
   cout << s->first << ' ' << s->second << endl;
   y.erase(1);
   cout << "1 deleted " << endl;
   cout << "Tree size is " << y.size() << endl;
   cout << "Elements in ascending order are" << endl;
   y.ascend();

   s = y.find(8);
   if (s == NULL)
      cout << "Search for 8 fails " << endl;
   cout << "Tree size is " << y.size() << endl;
   cout << "Elements in ascending order are" << endl;
   y.ascend();

   s = y.find(6);
   cout << "Search for 6 succeeds " << endl;
   cout << s->first << ' ' << s->second << endl;
   y.erase(6);
   cout << "6 deleted " << endl;
   cout << "Tree size is " << y.size() << endl;
   cout << "Elements in ascending order are" << endl;
   y.ascend();

   y.insert(pair<int, char>(1, 'a'));
   y.insert(pair<int, char>(6, 'f'));
   y.insert(pair<int, char>(3, 'c'));
   y.insert(pair<int, char>(4, 'e'));
   y.insert(pair<int, char>(1, 'b'));
   y.insert(pair<int, char>(6, 'g'));
   y.insert(pair<int, char>(3, 'd'));
   cout << "Tree size is " << y.size() << endl;
   cout << "Elements in ascending order are" << endl;
   y.ascend();
}
