
// selection sort added

#ifndef Chain_
#define Chain_

#include <iostream.h>
#include "cnode.h"
#include "xcept.h"

template <class T> class ChainIterator;

template<class T>
class Chain {
   friend ChainIterator<T>;
   public:
      Chain() {first = 0;}
      ~Chain();
      bool IsEmpty() const {return first == 0;}
      int Length() const; 
      bool Find(int k, T& x) const; 
      int Search(const T& x) const; 
      Chain<T>& Delete(int k, T& x); 
      Chain<T>& Insert(int k, const T& x);
      Chain<T>& SelectionSort();
      void Output(ostream& out) const;
   private:
      ChainNode<T> *first;  // pointer to first node
};

template<class T>
Chain<T>::~Chain()
{// Chain destructor. Delete all nodes in chain.
   ChainNode<T> *next;  // next node
   while (first) {
      next = first->link;
      delete first;
      first = next;
      }
}

template<class T>
int Chain<T>::Length() const
{// Return the number of elements in the chain.
   ChainNode<T> *current = first;
   int len = 0;
   while (current) {
     len++;
     current = current->link;
     }
   return len;
}

template<class T>
bool Chain<T>::Find(int k, T& x) const
{// Return the k'th element in the chain in x.
 // Return false if no k'th; return true otherwise.
   if (k < 1) return false;
   ChainNode<T> *current = first;
   int index = 1;  // index of current
   while (index < k && current) {
      current = current->link;
      index++;
      }
   if (current) {x = current->data;
                 return true;}
   return false; // no k'th element
}

template<class T>
int Chain<T>::Search(const T& x) const
{// Locate x.  Return position of x if found.
 // Return 0 if x not in the chain.
   ChainNode<T> *current = first;
   int index = 1;  // index of current
   while (current && current->data != x) {
      current = current->link;
      index++;
      }
   if (current) return index;
   return 0;
}

template<class T>
Chain<T>& Chain<T>::Delete(int k, T& x)
{// Delete k'th element of chain.
 // Throw OutOfBounds exception if no k'th element.
   if (k < 1 || !first)
      throw OutOfBounds(); // no k'th
   
   // p will eventually point to k'th node
   ChainNode<T> *p = first;

   // move p to k'th & remove from chain
   if (k == 1) // p already at k'th
      first = first->link; // remove
   else { // use q to get to k-1'st
      ChainNode<T> *q = first;
      for (int index = 1; index < k - 1 && q;
                          index++)
         q = q->link;
      if (!q || !q->link)
         throw OutOfBounds(); // no k'th
      p = q->link; // k'th
      q->link = p->link;} // remove from chain

   // save k'th element and free node p
   x = p->data;
   delete p;
   return *this;
}

template<class T>
Chain<T>& Chain<T>::Insert(int k, const T& x)
{// Insert x after the k'th element.
 // Throw OutOfBounds exception if no k'th element.
 // Pass NoMem exception if inadequate space.
   if (k < 0) throw OutOfBounds();

   // p will eventually point to k'th node
   ChainNode<T> *p = first;
   for (int index = 1; index < k && p;
                       index++)  // move p to k'th
      p = p->link;
   if (k > 0 && !p) throw OutOfBounds(); // no k'th

   // insert
   ChainNode<T> *y = new ChainNode<T>;
   y->data = x;
   if (k) {// insert after p
           y->link = p->link;
           p->link = y;}
   else {// insert as first element
         y->link = first;
         first = y;}
   return *this;
}


template<class T>
Chain<T>& Chain<T>::SelectionSort()
{// Sort *this using the selection sort method.
   if (!first) return *this;       // empty list

   // define cursors
   ChainNode<T> *AfterLast = 0,    // node after last one
                *MaxNode,          // node with max element
                *PreMax,           // node left of MaxNode
                *current,          // curent node
                *previous;         // node left of current

   // selection sort
   while (first->link != AfterLast) {
      // more than one element remains
      // do a selection pass
      MaxNode = first;
      PreMax = 0;
      current = first->link;
      previous = first;
      while (current->link != AfterLast) {
         // compare current and MaxNode
         // update MaxNode if necessary
         if (current->data > MaxNode->data) {
            // update PreMax and MaxNode
            PreMax = previous;
            MaxNode = current;
            }
         // move cursors forward one node
         previous = current;
         current = current->link;
         }
      if (current->data > MaxNode->data)
         // no node is to be moved
         // set for next pass
         AfterLast = current;
      else {
         // must bring MaxNode to right of current
         // first delete MaxNode from present location
         if (PreMax)
            // MaxNode is not the first node on the chain
            PreMax->link = MaxNode->link;
         else
            // MaxNode is the first node
            first = MaxNode->link;
         // now insert MaxNode after current
         MaxNode->link = current->link;
         current->link = MaxNode;
         // set for next pass
         AfterLast = MaxNode;
         }
      }

   return *this;
}

template<class T>
void Chain<T>::Output(ostream& out) const
{// Insert the chain elements into the stream out.
   ChainNode<T> *current;
   for (current = first; current;
                         current = current->link)
      out << current->data << "  ";
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const Chain<T>& x)
   {x.Output(out); return out;}

#endif
