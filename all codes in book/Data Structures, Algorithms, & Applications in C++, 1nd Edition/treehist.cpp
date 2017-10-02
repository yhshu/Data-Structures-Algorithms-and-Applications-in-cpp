// histogramming using a binary search tree

#include <iostream.h>
#include <stdlib.h>
#include "xcept.h"

class eType {
   friend void main(void);
   friend void Add1(eType&);
   friend ostream& operator <<(ostream&, eType);
   public:
      operator int() const {return key;}
   private:
      int key,    // element value
          count;  // frequency
};

ostream& operator<<(ostream& out, eType x)
   {out << x.key << " " << x.count << "   "; return out;}

void Add1(eType& e) {e.count++;}

#include "abst.h"

void main(void)
{// Histogram using a search tree.
   BSTree<eType,int> T;
   int n;  // number of elements
   cout << "Enter number of elements" << endl;
   cin >> n;

   // input elements and enter into tree
   for (int i = 1; i <= n; i++) {
      eType e;  // input element
      cout << "Enter element " << i << endl;
      cin >> e.key;
      e.count = 1;
      // put e in tree unless match already there
      // in latter case increase count by 1
      try {T.InsertVisit(e, Add1);}
      catch (NoMem)
         {cout << "Out of memory" << endl;
          exit(1);}
      }

   // output distinct elements and their counts
   cout << "Distinct elements and frequencies are"
        << endl;
   T.Ascend();
}
