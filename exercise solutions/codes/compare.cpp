
#include<iostream.h>
#include "compare.h"

void main(void)
{
   BinaryTree<int> a,b,x,y,z,u,v,w;
   y.MakeTree(1,a,a);
   z.MakeTree(2,a,a);
   x.MakeTree(3,y,z);
   y.MakeTree(4,x,a);
   y.PreOutput();
   y.InOutput();
   u.MakeTree(1,a,a);
   v.MakeTree(2,a,a);
   w.MakeTree(3,u,v);
   b.MakeTree(4,w,a);
   cout << "Result of compare is " << b.Compare(y) << endl;
   cout << "Result of compare is " << b.Compare(a) << endl;
   cout << "Result of compare is " << a.Compare(b) << endl;
   cout << "Result of compare is " << z.Compare(b) << endl;
}
