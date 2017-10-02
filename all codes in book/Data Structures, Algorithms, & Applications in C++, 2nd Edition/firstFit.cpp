// first fit bin packing

#include <iostream>
#include "completeWinnerTree.h"
#include "binType.h"

using namespace std;
   
void firstFitPack(int *objectSize, int numberOfObjects,
                                   int binCapacity)
{// output first fit packing into bins of size binCapacity
 // objectSize[1:numberOfObjects] are the object sizes

   int n = numberOfObjects;             // number of objects

   // initialize n bins and winner tree
   binType *bin = new binType [n + 1];  // bins
   for (int i = 1; i <= n; i++)
      bin[i].unusedCapacity = binCapacity;
   completeWinnerTree<binType> winTree(bin, n);
   
   // pack objects into bins
   for (int i = 1; i <= n; i++)
   {// put object i into a bin
      // find first bin with enough capacity
      int child = 2;  // start search at left child of root
      while (child < n)
      {
         int winner = winTree.winner(child);
         if (bin[winner].unusedCapacity < objectSize[i])
            child++ ;  // first bin is in right subtree
         child *= 2;   // move to left child
      }

      int binToUse;          // will be set to bin to use
      child /= 2;            // undo last left-child move
      if (child < n)
      {// at a tree node
         binToUse = winTree.winner(child);
         // if binToUse is right child, need to check
         // bin binToUse-1.  No harm done by checking
         // bin binToUse-1 even if binToUse is left child.
         if (binToUse > 1 &&
             bin[binToUse - 1].unusedCapacity >= objectSize[i])
            binToUse--;
       }
       else  // arises when n is odd
          binToUse = winTree.winner(child / 2);
 
       cout << "Pack object " << i << " in bin "
            << binToUse << endl;
       bin[binToUse].unusedCapacity -= objectSize[i];
       winTree.rePlay(binToUse);
   }
}


// test program
void main(void)
{
   int n, binCapacity; // number of objects and bin capacity
   cout << "Enter number of objects and bin capacity"
        << endl;
   cin >> n >> binCapacity;
   if (n < 2)
   {
      cout << "Too few objects" << endl;
      exit(1);
   }
   int *objectSize = new int[n+1];
   
   for (int i = 1; i <= n; i++)
   {
     cout << "Enter space requirement of object "
          << i << endl;
     cin >> objectSize[i];
     if (objectSize[i] > binCapacity)
     {
       cout << "Object too large to fit in a bin"
            << endl;
       exit(1);}
     }
   firstFitPack(objectSize, n, binCapacity);
}
