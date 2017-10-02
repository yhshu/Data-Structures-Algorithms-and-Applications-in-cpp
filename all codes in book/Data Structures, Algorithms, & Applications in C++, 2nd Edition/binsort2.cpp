// test bin sort as member of chain class

#include <iostream>
#include "studentRecord2.h"
#include "chainWithBinSort.h"

int main(void)
{
   studentRecord s;
   chain<studentRecord> theChain;
   for (int i = 1; i <= 20; i++)
   {
      s.score = i/2;
      s.name = new string(s.score, 'a');
      theChain.insert(0,s);
   }
   cout << "The unsorted chain is" << endl;
   cout << "  " << theChain << endl;
   theChain.binSort(10);
   cout << "The sorted chain is" << endl;
   cout << "  " << theChain << endl;
}
