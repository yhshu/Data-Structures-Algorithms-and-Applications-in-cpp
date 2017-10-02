// test linked binary tree class

#include <iostream>
#include "linkedBinaryTree.h"

using namespace std;

int main(void)
{
   linkedBinaryTree<int> a,x,y,z;
   y.makeTree(1,a,a);
   z.makeTree(2,a,a);
   x.makeTree(3,y,z);
   y.makeTree(4,x,a);
   cout << "Number of nodes = ";
   cout << y.size() << endl;
   cout << "height = ";
   cout << y.height() << endl;
   cout << "Preorder sequence is ";
   y.preOrderOutput();
   cout << "Inorder sequence is ";
   y.inOrderOutput();
   cout << "Postorder sequence is ";
   y.postOrderOutput();
   cout << "Level order sequence is ";
   y.levelOrderOutput();

   return 0;
}
