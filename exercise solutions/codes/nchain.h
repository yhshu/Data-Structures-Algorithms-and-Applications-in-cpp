

// bubble sort added

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
      Chain<T>& BubbleSort();
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
Chain<T>& Chain<T>::BubbleSort()
{// Sort *this using the bubble sort method.
   if (!first) return *this;       // empty list

   // define cursors
   ChainNode<T> *AfterLast = 0,    // node after last one
                *current,          // curent node
                *next,             // node right of current
                *previous;         // node left of current

   // bubble sort
   while (first->link != AfterLast) {
      // more than one element remains
      // do a bubbling pass
      current = first;
      next = first->link;
      previous = 0;
      while (next != AfterLast)
         // compare current and next and
         // swap nodes if necessary
         if (current->data > next->data) {
            // swap the nodes
            if (previous) previous->link = next;
            else first = next;
            current->link = next->link;
            next->link = current;
            previous = next;
            next = current->link;
            }
         else {// move cursors forward one node
               previous = current;
               current = next;
               next = next->link;
               }
         //  need to go only as far as previous
         AfterLast = current;
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
