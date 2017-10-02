// test binary search tree with duplicate class

#include <iostream.h>
#include <stdlib.h>
#include "datatype.h"
#include "dbst.h"

DBSTree<DataType,int> y;

void main(void)
{
   DataType q;
   q.key = 1; q.ID = 'a';
   y.Insert(q);
   q.key = 6; q.ID = 'b';
   y.Insert(q);
   q.key = 6; q.ID = 'c';
   y.Insert(q);
   q.key = 8; q.ID = 'd';
   y.Insert(q);
   q.key = 8; q.ID = 'e';
   y.Insert(q);
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   DataType s;
   try {y.Delete(4,s);}
   catch (BadInput)
      {cout << "Delete of 4 fails " << endl;}
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   y.Delete(8,s);
   cout << "Delete of 8 succeeds " << endl;
   cout << s.key << ' ' << s.ID << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   y.Delete(6,s);
   cout << "Delete of 6 succeeds " << endl;
   cout << s.key << ' ' << s.ID << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   y.Delete(6,s);
   cout << "Delete of 6 succeeds " << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   int x;
   y.FindGE(4,x);
   cout << "Smallest key >= 4 is " << x << endl;
}
