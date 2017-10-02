
#include <iostream.h>
#include "twothree.h"


void main(void)
{
   // define a 2-3 tree with null element 0
   TwoThree<int,int> y(0);

   // first test insert and ascending output
   y.Insert(21).Insert(29).Insert(30);
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   // cause leftmost node to split
   y.Insert(9).Insert(4);
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   // cause middle leaf and root to split
   y.Insert(14).Insert(15);
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   // cause righmost leaf to split
   y.Insert(32).Insert(31);
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   // cause a double split
   y.Insert(22).Insert(23);
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Insert(24).Insert(25);

   // now test the search operation
   int x;
   if (!y.Search(1,x)) cout << "1 was not found" << endl;
   if (!y.Search(28,x)) cout << "28 was not found" << endl;
   if (!y.Search(40,x)) cout << "40 was not found" << endl;
   if (y.Search(23,x)) cout << "23 was found" << endl;
   if (y.Search(30,x)) cout << "30 was found" << endl;

   // cause triple split
   y.Insert(27).Insert(28);
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();

   // now test the delete operation
   y.Delete(4,x);
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Delete(14,x);
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Delete(21,x);
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Delete(30,x);
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Delete(32,x);
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Delete(28,x);
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
 
   // do several inserts
   y.Insert(26).Insert(18).Insert(36).Insert(40).Insert(32).Insert(34);
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();

  // delete from the interior
   y.Delete(29,x);
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Delete(22,x);
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Delete(27,x);
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Delete(25,x);
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Delete(36,x);
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Delete(26,x).Delete(15,x).Delete(32,x).Delete(23,x);
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Delete(34,x).Delete(24,x).Delete(18,x);
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Delete(31,x).Delete(9,x).Delete(40,x);
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
 
}
