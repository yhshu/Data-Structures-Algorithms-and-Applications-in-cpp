
// chain using simulated pointers

#ifndef SimChain_
#define SimChain_

#include <stdlib.h>
#include <iostream.h>
#include "simul.h"
#include "xcept.h"

template <class T> class SimChainIterator;

template<class T>
class SimChain {
   friend SimChainIterator<T>;
   public:
      SimChain() {first = -1;}
      ~SimChain() {Destroy();} 
      void Destroy(); // make list null
      int Length() const;
      bool Find(int k, T& x) const; 
      int Search(const T& x) const; 
      SimChain<T>& Delete(int k, T& x); 
      SimChain<T>& Insert(int k, const T& x); 
      void Output(ostream& out) const;
   private:
      int first;  // index of first node
      static SimSpace<T> S;
};

template<class T>
void SimChain<T>::Destroy()
{// Deallocate chain nodes.
   int next;
   while (first != -1) {
      next = S.node[first].link;
      S.Deallocate(first);
      first = next;
      }
}

template<class T>
int SimChain<T>::Length() const
{// Return the number of elements in the chain.
   int current = first,  // chain node cursor
       len = 0;          // element counter
   while (current != -1) {
      current = S.node[current].link;
      len++;
      }
   return len;
}

template<class T>
bool SimChain<T>::Find(int k, T& x) const
{// Set x to the k'th element in the chain.
 // Return false if no k'th; return true otherwise.
   if (k < 1) return false;
   int current = first,  // cursor for chain nodes
       index = 1;        // index of current node

   // move current to k'th node
   while (index < k && current != -1) {
      current = S.node[current].link;
      index++;
      }

   // verify that we got to the k'th node
   if (current != -1) {x = S.node[current].data;
                       return true;}
   return false; // no k'th element
}

template<class T>
int SimChain<T>::Search(const T& x) const
{// Locate x.  Return position of x if found.
 // Return 0 if x not in the chain.
   int current = first,  // cursor for chain nodes
       index = 1;        // index of current node

   // search the chain left to right
   while (current != -1 && S.node[current].data != x) {
      current = S.node[current].link;
      index++;
      }
   return ((current >= 0) ? index : 0);
}


template<class T>
SimChain<T>& SimChain<T>::Delete(int k, T& x)
{// Set x to the k'th element and delete it.
 // Throw OutOfBounds exception if no k'th element.

   if (k < 1 || first == -1)
      throw OutOfBounds(); // no k'th
   
   // p will eventually point to k'th node
   int p = first;

   // move p to k'th & remove from chain
   if (k == 1) // p already at k'th
      first = S.node[first].link; // remove from chain
   else { // use q to get to k-1'st
      int q = first;
      for (int index = 1; index < k - 1 && q != -1;
                          index++)
         q = S.node[q].link;

      // verify presence of k'th element
      if (q == -1 || S.node[q].link == -1)
         throw OutOfBounds(); // no k'th

      // make p point to k'th element
      p = S.node[q].link;

      // remove k'th element from chain
      S.node[q].link = S.node[p].link;
      }

   // save k'th element and free node p
   x = S.node[p].data;
   S.Deallocate(p);
   return *this;
}

template<class T>
SimChain<T>& SimChain<T>::Insert(int k, const T& x)
{// Insert x after the k'th element.
 // Throw OutOfBounds exception if no k'th element.
 // Pass NoMem exception if inadequate space.

   if (k < 0) throw OutOfBounds();

   // define a cursor p that will
   // eventually point to k'th node
   int p = first;

   // move p to k'th node
   for (int index = 1; index < k && p != -1;
                       index++)
      p = S.node[p].link;

   // verify presence of k'th element
   if (k > 0 && p == -1)
      throw OutOfBounds();

   // prepare a new node for insertion
   int y = S.Allocate();
   S.node[y].data = x;

   // insert the new node into the chain
   // first check if the new node is to be the
   // first one in the chain
   if (k) {// insert after p
           S.node[y].link = S.node[p].link;
           S.node[p].link = y;}
   else {// insert as first element
         S.node[y].link = first;
         first = y;}

   return *this;
}

template<class T>
void SimChain<T>::Output(ostream& out) const
{
   for (int current = first; current != -1;
                      current = S.node[current].link)
      out << S.node[current].data << ' ';
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const SimChain<T>& x)
   {x.Output(out); return out;}

#endif
