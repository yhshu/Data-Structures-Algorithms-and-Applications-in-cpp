// bin sort as member of chain class

#include <iostream.h>
#include "binnode2.h"
#include "nchain.h"

void main(void)
{
   Node x;
   Chain<Node> L;
   for(int i = 1; i <= 20; i++) {
   x.score = i/2;
   L.Insert(0,x); }
   L.BinSort(10);
   cout << L << endl;
}
