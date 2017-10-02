// file simul.h
// simulated pointers

#ifndef SimSpace_
#define SimSpace_

#include <stdlib.h>
#include <iostream.h>
#include <stdlib.h>
#include "snode.h"
#include "xcept.h"


template <class T> class SimChain;

template <class T>
class SimSpace {
   friend SimChain<T>;
   public:
      SimSpace(int MaxSpaceSize = 100);
      ~SimSpace() {delete [] node;}
      int Allocate(); // allocate a node
      void Deallocate(int& i); // deallocate node i
   private:
      int NumberOfNodes, first;
      SimNode<T> *node; // array of nodes
};

template<class T>
SimSpace<T>::SimSpace(int MaxSpaceSize)
{// Constructor.
   NumberOfNodes = MaxSpaceSize;
   node = new SimNode<T> [NumberOfNodes];
   // initialize available space list
   // create a chain of nodes
   for (int i = 0; i < NumberOfNodes-1; i++)
      node[i].link = i+1;
   // last node of chain
   node[NumberOfNodes-1].link = -1;
   // first node of chain
   first = 0;
}

template<class T>
int SimSpace<T>::Allocate()
{// Allocate a free node.
   if (first == -1) throw NoMem();
   int i = first;         // allocate first node
   first = node[i].link;  // first points to next
                          // free node
   return i;
}

template<class T>
void SimSpace<T>::Deallocate(int& i)
{// Free node i.
   // make i first node on avail list
   node[i].link = first;
   first = i;
   i = -1;
}

#endif
