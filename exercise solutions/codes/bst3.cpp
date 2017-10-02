
#include <iostream.h>
#include "bst3.h"
#include "datatype.h"

BSTree<DataType,int> y;

void main(void)
{
   DataType q;
   q.key = 1; q.ID = 'a';
   y.Insert(q);
   q.key = 6; q.ID = 'b';
   y.Insert(q);
   q.key = 4; q.ID = 'c';
   y.Insert(q);
   q.key = 8; q.ID = 'd';
   y.Insert(q);
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   DataType s;
   y.DeleteMax(s);
   cout << "Delete of max element succeeds " << endl;
   cout << s.key << ' ' << s.ID << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   y.DeleteMax(s);
   cout << "Delete of max element succeeds " << endl;
   cout << s.key << ' ' << s.ID << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   y.DeleteMax(s);
   cout << "Delete of max element succeeds " << endl;
   cout << s.key << ' ' << s.ID << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   try {y.Delete(6,s);}
   catch (BadInput)
      {cout << "Delete of 6 fails " << endl;}
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
}
