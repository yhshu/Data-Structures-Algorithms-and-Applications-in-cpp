
// best fit bin packing

#include <iostream>
#include "dBinarySearchTreeWithGE.h"

using namespace std;

void bestFitPack(int *objectSize, int numberOfObjects, int binCapacity)
{// Output best-fit packing into bins of size binCapacity.
 // objectSize[1:numberOfObjects] are the object sizes.
   int n = numberOfObjects;
   int binsUsed = 0;
   dBinarySearchTreeWithGE<int,int> theTree;  // tree of bin capacities
   pair<int, int> theBin;
   
   // pack objects one by one
   for (int i = 1; i <= n; i++)
   {// pack object i
      // find best bin
      pair<const int, int> *bestBin = theTree.findGE(objectSize[i]);
      if (bestBin == NULL)
      {// no bin large enough, start a new bin
         theBin.first = binCapacity;
         theBin.second = ++binsUsed;
      }
      else
      {// remove best bin from theTree
         theBin = *bestBin;
         theTree.erase(bestBin->first);
      }
   
      cout << "Pack object " << i << " in bin "
           << theBin.second << endl;

      // insert bin in tree unless bin is full
      theBin.first -= objectSize[i];
      if (theBin.first > 0)
         theTree.insert(theBin);
   }
}

// test program
int main(void)
{
   cout << "Enter number of objects and bin capacity" << endl;
   int numberOfObjects, binCapacity;
   cin >> numberOfObjects >> binCapacity;
   if (numberOfObjects < 2)
   {
      cout << "Too few objects" << endl;
      exit(1);
   }

   // input the object sizes objectSize[1:numberOfObjects]
   int *objectSize = new int [numberOfObjects + 1];
   for (int i = 1; i <= numberOfObjects; i++)
   {
      cout << "Enter space requirement of object " << i << endl;
      cin >> objectSize[i];
      if (objectSize[i] > binCapacity)
      {
        cout << "Object too large to fit in a bin" << endl;
        exit(1);
      }
   }

   // output the packing
   bestFitPack(objectSize, numberOfObjects, binCapacity);
}
