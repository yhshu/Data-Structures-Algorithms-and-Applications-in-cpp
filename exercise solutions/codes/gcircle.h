

// circular linked list
// includes arbitrary delete

#ifndef Circular_
#define Circular_

template <class T> class CircularIterator;

#include <iostream.h>
#include "cnode.h"
#include "xcept.h"

template<class T>
class Circular {
   friend CircularIterator<T>;
   public:
      Circular() {location = last = 0;}
      ~Circular();
      bool IsEmpty() const {return last == 0;}
      int Length() const; 
      bool Find(int k, T& x) const; 
      int Search(const T& x) const; 
      Circular<T>& Delete(int k, T& x); 
      Circular<T>& Delete(T& x); 
      void MoveForward(int k); 
      Circular<T>& Insert(int k, const T& x);
      void Output(ostream& out) const;
   private:
      ChainNode<T> *last,     // pointer to last node
                   *location; // may point to any node
};

template<class T>
Circular<T>::~Circular()
{// Circular destructor. Delete all nodes.
   if (!last) return;         // list is empty

   // delete all nodes
   ChainNode<T> *current = last->link,
                              // current node
                *next;        // next node
   while (current != last) {
      next = current->link;
      delete current;
      current = next;
      }
   delete last;
}

template<class T>
int Circular<T>::Length() const
{// Return the number of elements in the list.
   if (!last) return 0;  // list is empty

   // count nodes
   ChainNode<T> *current = last->link;
   int len = 0;
   while (current != last) {
     len++;
     current = current->link;
     }
   len++;  // for last node
   return len;
}

template<class T>
bool Circular<T>::Find(int k, T& x) const
{// Set x to the k'th element in the list.
 // Return false if no k'th; return true otherwise.
   if (k < 1 || !last) return false;

   ChainNode<T> *current = last->link;
   int index = 1;  // index of current
   while (index < k && current != last) {
      // move to next node
      current = current->link;
      index++;
      }
   if (index == k) {x = current->data;
                    return true;}
   return false; // no k'th element
}

template<class T>
int Circular<T>::Search(const T& x) const
{// Locate x.  Return position of x if found.
 // Return 0 if x not in the chain.
   if (!last) return 0;  // list is empty

   // examine nodes
   ChainNode<T> *current = last->link;
   int index = 1;  // index of current
   while (current->data != x && current != last) {
      // move to next node
      current = current->link;
      index++;
      }
   if (current->data == x) return index;
   return 0;
}

template<class T>
Circular<T>& Circular<T>::Delete(int k, T& x)
{// Set x to the k'th element and delete it.
 // Throw OutOfBounds exception if no k'th element.
   if (k < 1 || !last)
      throw OutOfBounds(); // no k'th
   
   // p will eventually point to k'th node
   // and q to k-1'st node
   ChainNode<T> *p = last->link,
                *q = last;

   // move p to k'th & remove from list
   if (k == 1) {// p already at k'th
      if (p != last) // nonempty list remains
         last->link = p->link;} // remove
   else { // move q to k-1'st
      q = p;
      for (int index = 1; index < k - 1
                && q != last; index++)
         q = q->link;
      if (q == last)
         throw OutOfBounds(); // no k'th
      p = q->link; // k'th
      q->link = p->link;} // remove

   // save k'th element and free node p
   x = p->data;
   if (p == last)  // check if new list is empty
      if (k == 1)  // new list is empty
         last = 0;
      else // not empty
         last = q;
   if (location == p) // reset location
      location = 0;
   delete p;
   return *this;
}

template<class T>
Circular<T>& Circular<T>::Delete(T& x)
{// Set x to the element that location
 // points to and delete that element.
 // Throw OutOfBounds exception if location is 0.
   if (!location)
      throw OutOfBounds(); // no element to delete
   
   x = location->data;
   // p will eventually point to node that
   // is to be deleted
   ChainNode<T> *p;
   if (last->link == last) {
      // remaining list is empty
      p = last;
      last = 0;
      }
   else {// nonempty list is left
      p = location->link;
      // copy fields from p
      location->data = p->data;
      location->link = p->link;
      if (p == last) last = location;
      }

   location = 0;
   delete p;
   return *this;
}

template<class T>
void Circular<T>::MoveForward(int k)
{// Move location forward by k elements.
 // Throw BadInput exception if there aren't
 // k elements to the right of the current location.
   if (!location && k > 0 && last) {
      //  move forward by at least one from
      // left of nonempty list
      location = last->link;
      k--;
      }
   for (int i = 1; i <= k; i++) {
      // move forward by one node
      if (location == last) // at last node
         throw BadInput();
      location = location->link;
      }
}

template<class T>
Circular<T>& Circular<T>::Insert(int k, const T& x)
{// Insert x after the k'th element.
 // Throw OutOfBounds exception if no k'th element.
 // Pass NoMem exception if inadequate space.
   if (k < 0) throw OutOfBounds();

   // p will eventually point to k'th node
   ChainNode<T> *p = last;
   if (k) {// advance p to k'th node
      if (!last) throw OutOfBounds();  // empty list
      p = p->link;
      int index = 1;
      for (; index < k && p != last;
             index++)  // move p to k'th
         p = p->link;
      if (index != k) throw OutOfBounds();} // no k'th

   // insert
   ChainNode<T> *y = new ChainNode<T>;
   y->data = x;
   if (k) {// insert after p
           y->link = p->link;
           p->link = y;
           if (p == last) last = y;}
   else // insert as first element
        if (last) {y->link = last->link;
                   last->link = y;}
        else {last = y;
              y->link = y;}

   return *this;
}

template<class T>
void Circular<T>::Output(ostream& out) const
{// Insert the chain elements into the stream out.
   if (!last) return;
   ChainNode<T> *current;
   for (current = last->link; current != last;
                         current = current->link)
      out << current->data << "  ";
  // output last node
  out << current->data << "  ";
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const Circular<T>& x)
   {x.Output(out); return out;}

#endif
