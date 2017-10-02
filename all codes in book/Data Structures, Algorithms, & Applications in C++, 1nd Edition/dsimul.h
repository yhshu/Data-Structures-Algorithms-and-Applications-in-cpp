// dual available space list version of a
// simulated pointer space
#ifndef SimSpace_
#define SimSpace_
#include<stdlib.h>
#include <iostream.h>
#include <stdlib.h>
#include "snode.h"
#include "xcept.h"

template <class T>
class SimSpace {
   public:
      SimSpace(int MaxSpaceSize = 100); // constructor
      ~SimSpace() {delete [] node;} // destructor
      int Allocate(); // allocate a node
      void Deallocate(int& i); // deallocate node i
      void DeallocateCircular(int& c); // deallocate circular list
   private:
      int NumberOfNodes, first1, first2;
      SimNode<T> *node;
};

template<class T>
SimSpace<T>::SimSpace(int MaxSpaceSize)
{// Dual available list constructor.
   NumberOfNodes = MaxSpaceSize;
   node = new SimNode<T> [NumberOfNodes];
   // initialize available space lists
   first1 = 0;
   first2 = -1;
}

template<class T>
int SimSpace<T>::Allocate()
{// Allocate a free node.
   if (first2 == -1) {// 2nd list empty
      if (first1 == NumberOfNodes) throw NoMem();
      return first1++;}
   // allocate first node of chain
   int i = first2;
   first2 = node[i].link;
   return i;
}

template<class T>
void SimSpace<T>::Deallocate(int& i)
{// Free node i.
   node[i].link = first2;
   first2 = i;
   i = -1;
}

template<class T>
void SimSpace<T>::DeallocateCircular(int& c)
{// Deallocate the circular list c.
   if (c != -1) {
      int next = node[c].link;
      node[c].link = first2;
      first2 = next;
      c = -1;
      }
}

#endif
