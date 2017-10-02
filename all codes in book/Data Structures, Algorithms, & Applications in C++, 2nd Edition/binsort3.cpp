// bin sort on different criteria

#include <iostream>
#include "studentRecord4.h"
#include "chainWithBinSort.h"

inline int f1(studentRecord& s) {return s.exam1;}
inline int f2(studentRecord& s) {return s.exam2;}
inline int f3(studentRecord& s)
   {return s.exam1 + s.exam2 + s.exam3;}

int main(void)
{
   studentRecord x;
   chain<studentRecord> theChain;
   for (int i = 1; i <= 20; i++)
   {
      x.exam1 = i/2;
      x.exam2 = 20 - i;
      x.exam3 = rand() % 100;
      x.name = i;
      theChain.insert(0,x);
   }
   theChain.binSort(10, f1);
   cout << "Sort on exam 1" << endl;
   cout << "  " << theChain << endl;
   theChain.binSort(20, f2);
   cout << "Sort on exam 2" << endl;
   cout << "  " << theChain << endl;
   theChain.binSort(130, f3);
   cout << "Sort on sum of exams" << endl;
   cout << "  " << theChain << endl;
}
