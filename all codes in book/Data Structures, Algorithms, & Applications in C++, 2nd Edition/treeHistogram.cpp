// histogramming using a binary search tree

#include <iostream>
#include "binarySearchTreeWithVisit.h"
void add1(int& count) {count++;}


int main(void)
{// Histogram using a search tree.
   int n;  // number of elements
   cout << "Enter number of elements" << endl;
   cin >> n;

   // input elements and enter into tree
   binarySearchTreeWithVisit<int, int> theTree;
   for (int i = 1; i <= n; i++)
   {
      pair<int, int> thePair;  // input element
      cout << "Enter element " << i << endl;
      cin >> thePair.first;    // key
      thePair.second = 1;      // frequency
      // insert thePair in tree unless match already there
      // in latter case increase count by 1
      theTree.insert(thePair, add1);
   }

   // output distinct elements and their counts
   cout << "Distinct elements and frequencies are"
        << endl;
   theTree.ascend();
}
