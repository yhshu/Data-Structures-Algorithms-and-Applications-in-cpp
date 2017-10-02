// bin sort on different criteria

#include <iostream.h>
#include <stdlib.h>
#include "binnode4.h"
#include "mchain.h"

inline int F1(Node& x) {return x.exam1;}
inline int F2(Node& x) {return x.exam2;}
inline int F3(Node& x)
   {return x.exam1 + x.exam2 + x.exam3;}

void main(void)
{
   Node x;
   Chain<Node> L;
   for (int i = 1; i <= 20; i++) {
      x.exam1 = i/2;
      x.exam2 = 20 - i;
      x.exam3 = rand() % 100;
      x.name = i;
      L.Insert(0,x);}
   L.BinSort(10, F1);
   cout << "Sort on exam 1" << endl;
   cout << L << endl;
   L.BinSort(20, F2);
   cout << "Sort on exam 2" << endl;
   cout << L << endl;
   L.BinSort(130, F3);
   cout << "Sort on sum of exams" << endl;
   cout << L << endl;
}
