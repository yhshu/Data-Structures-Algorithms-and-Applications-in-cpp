// best fit bin packing

#include <iostream.h>
#include <stdlib.h>
#include "dbst2.h"
#include "xcept.h"

class BinNode {
   friend void BestFitPack(int *, int, int);
   friend ostream& operator<<(ostream&, BinNode);
   public:
      operator int() const {return avail;}
   private:
      int ID,     // bin identifier
          avail;  // available capacity
};

ostream& operator<<(ostream& out, BinNode x)
   {out << "Bin " << x.ID << " " << x.avail;
    return out;}

void BestFitPack(int s[], int n, int c)
{
   int b = 0;                // number of bins used
   DBSTree<BinNode, int> T;  // tree of bin capacities
   
   // pack objects one by one
   for (int i = 1; i <= n; i++) {// pack object i
      BinNode e;  // corresponding node
      // find and delete best bin from tree
      try {T.DeleteGE(s[i], e);}
      catch (BadInput)
         {// no bin large enough
          // start a new bin
          e = *(new BinNode);
          e.ID = ++b;
          e.avail = c;}
   
      cout << "Pack object " << i << " in bin "
           << e.ID << endl;

      // update available capacity and put bin
      // in tree unless avail capacity is zero
      e.avail -= s[i];
      if (e.avail) T.Insert(e);
      }
}

void main(void)
{
   int n, // number of objects
       c; // bin capacity
   cout << "Enter number of objects and bin capacity" << endl;
   cin >> n >> c;
   if (n < 2) {cout << "Too few objects" << endl;
               exit(1);}

   int *s;  // array to hold object sizes
   try {s = new int[n+1];}
   catch (NoMem)
      {cout << "Out of memory" << endl;
       exit(1);}
   
   for (int i = 1; i <= n; i++) {
     cout << "Enter space requirement of object " << i << endl;
     cin >> s[i];
     if (s[i] > c) {
       cout << "Object too large to fit in a bin" << endl;
       exit(1);}}
   BestFitPack(s, n, c);
}
