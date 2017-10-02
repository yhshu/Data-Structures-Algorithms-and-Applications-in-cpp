
#include <iostream.h>
#include "iavl.h"


void main(void)
{
   IndexedAVLtree<int,int> y;

   // first test insert and ascending output
   y.Insert(21).Insert(26).Insert(30);
   cout << "An RR rotation has been done" << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Insert(9).Insert(4);
   cout << "An LL rotation has been done" << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Insert(14);
   cout << "An LR rotation has been done" << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Insert(28);
   cout << "An RL rotation has been done" << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Insert(18).Insert(15);
   cout << "An RL rotation has been done" << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Insert(10);
   cout << "An RL rotation has been done" << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Insert(2);
   cout << "An LL rotation has been done" << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Insert(3);
   cout << "An LR rotation has been done" << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Insert(7);
   cout << "An LR rotation has been done" << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   cout << endl;

   // test indexed search
   int x;
   for (int i = 1; i <= 13; i++) {
      y.IndexedSearch(i,x);
      cout << "Element " << i << " is " << x << endl;
      }
   cout << endl;

   // now test the delete operation
   y.Delete(2,x).Delete(3,x);
   cout << "An L0/RR rotation has been done" << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Delete(10,x);
   cout << "An R-1/LR rotation has been done" << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Delete(18,x).Delete(4,x).Delete(9,x);
   cout << "An L-1/RR rotation has been done" << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Delete(30,x).Delete(14,x).Delete(7,x).Delete(15,x);
   cout << "An L1/RL rotation has been done" << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Insert(10).Insert(5).Insert(30).Insert(29);
   y.Delete(29,x).Delete(28,x).Delete(30,x);
   cout << "An R0/LL rotation has been done" << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
   y.Insert(3);
   y.Delete(26,x).Delete(21,x);
   cout << "An R1/LL rotation has been done" << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();
 
   // empty out and create larger tree
   y.Delete(5,x).Delete(3,x).Delete(10,x);

   y.Insert(40).Insert(5).Insert(50).Insert(3);
   y.Insert(10).Insert(45).Insert(60);
   y.Insert(1).Insert(7).Insert(30).Insert(41);
   y.Insert(47).Insert(55).Insert(70).Insert(20);
   y.Insert(46).Insert(52).Insert(65).Insert(72).Insert(68);

   // should cause multiple rotations
   y.Delete(3,x);
   cout << "Two L-1/RR rotations have been done" << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();

   y.Insert(58).Insert(56).Insert(74).Insert(71).Insert(75);
   // should cause multiple rotations
   y.Delete(5,x).Delete(1,x).Delete(7,x);
   y.Delete(20,x).Delete(10,x).Delete(30,x);
   cout << "An L1/RL followed by two L-1/RR rotations have been done" << endl;
   cout << "Elements in ascending order are" << endl;
   y.Ascend();
   cout << "Elements in postorder order are" << endl;
   y.PostOut();

   cout << endl;

   // test indexed search again
   for (i = 1; i <= 18; i++) {
      y.IndexedSearch(i,x);
      cout << "Element " << i << " is " << x << endl;
      }
   cout << endl;

  // now test indexed delete
  y.IndexedDelete(7,x);
  cout << "Element 7 deleted " << x << endl;
  y.IndexedDelete(9,x);
  cout << "Element 9 deleted " << x << endl;
  y.IndexedDelete(12,x);
  cout << "Element 12 deleted " << x << endl;
  y.IndexedDelete(8,x);
  cout << "Element 8 deleted " << x << endl;
  y.IndexedDelete(10,x);
  cout << "Element 10 deleted " << x << endl;
  cout << "Elements in ascending order are" << endl;
  y.Ascend();
}
