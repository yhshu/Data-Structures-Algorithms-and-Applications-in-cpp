

// doubly linked circular list

#ifndef DoubleCircular_
#define DoubleCircular_

template <class T> class DoubleCircularIterator;

#include <iostream.h>
#include "dnode.h"
#include "xcept.h"

template<class T>
class DoubleCircular {
   friend DoubleCircularIterator<T>;
   public:
      DoubleCircular() {last = 0;}
      ~DoubleCircular();
      bool IsEmpty() const {return last == 0;}
      int Length() const; 
      bool Find(int k, T& x) const; 
      int Search(const T& x) const; 
      DoubleCircular<T>& Delete(int k, T& x); 
      DoubleCircular<T>& Insert(int k, const T& x);
      void Output(ostream& out) const;
   private:
      DoubleNode<T> *last; // pointer to rightmost node
};

template<class T>
DoubleCircular<T>::~DoubleCircular()
{// DoubleCircular destructor. Delete all nodes.
   if (!last) return;         // list is empty

   // delete all nodes
   DoubleNode<T> *current = last->right,
                               // current node
                 *next;        // next node
   while (current != last) {
      next = current->right;
      delete current;
      current = next;
      }
   delete last;
}

template<class T>
int DoubleCircular<T>::Length() const
{// Return the number of elements in the list.
   if (!last) return 0;  // list is empty

   // count nodes
   DoubleNode<T> *current = last->right;
   int len = 0;
   while (current != last) {
     len++;
     current = current->right;
     }
   len++;  // for last node
   return len;
}

template<class T>
bool DoubleCircular<T>::Find(int k, T& x) const
{// Set x to the k'th element in the list.
 // Return false if no k'th; return true otherwise.
   if (k < 1 || !last) return false;

   DoubleNode<T> *current = last->right;
   int index = 1;  // index of current
   while (index < k && current != last) {
      // move to next node
      current = current->right;
      index++;
      }
   if (index == k) {x = current->data;
                    return true;}
   return false; // no k'th element
}

template<class T>
int DoubleCircular<T>::Search(const T& x) const
{// Locate x.  Return position of x if found.
 // Return 0 if x not in the chain.
   if (!last) return 0;  // list is empty

   // examine nodes
   DoubleNode<T> *current = last->right;
   int index = 1;  // index of current
   while (current->data != x && current != last) {
      // move to next node
      current = current->right;
      index++;
      }
   if (current->data == x) return index;
   return 0;
}

template<class T>
DoubleCircular<T>& DoubleCircular<T>::Delete(int k, T& x)
{// Set x to the k'th element and delete it.
 // Throw OutOfBounds exception if no k'th element.
   if (k < 1 || !last)
      throw OutOfBounds(); // no k'th
   
   // p will eventually point to k'th node
   DoubleNode<T> *p = last->right;
   int index = 1;  // index of p

   // move p to k'th
   for (; index < k && p != last; index++)
      p = p->right;

   // make sure p is at the k'th element
   if (index != k) throw OutOfBounds(); // no k'th

   // remove p from list
   p->right->left = p->left;
   p->left->right = p->right;

   // save k'th element, update last, and free node p
   x = p->data;
   if (p == last)  // check if new list is empty
      if (k == 1)  // new list is empty
         last = 0;
      else // not empty
         last = last->left;
   delete p;

   return *this;
}

template<class T>
DoubleCircular<T>& DoubleCircular<T>::Insert(int k, const T& x)
{// Insert x after the k'th element.
 // Throw OutOfBounds exception if no k'th element.
 // Pass NoMem exception if inadequate space.
   if (k < 0) throw OutOfBounds();

   if (k) {// locate k'th node
      if (!last) throw OutOfBounds();  // empty list

      // p will eventually point to k'th node
      DoubleNode<T> *p = last->right;
      int index = 1;
      for (; index < k && p != last;
             index++)  // move p to k'th
         p = p->right;
      if (index != k) throw OutOfBounds(); // no k'th

      // insert after p
      DoubleNode<T> *y = new DoubleNode<T>;
      y->data = x;
      y->right = p->right;
      y->right->left = y;
      p->right = y;
      y->left = p;
      if (p == last) last = y;
      }
   else {// insert as first element
         DoubleNode<T> *y = new DoubleNode<T>;
         y->data = x;
         if (last) {// insert into nonempty list
            y->right = last->right;
            y->right->left = y;
            last->right = y;
            y->left = last;
            }
         else {// insert into an empty list
               last = y;
               y->left = y;
               y->right = y;
               }
         }

   return *this;
}

template<class T>
void DoubleCircular<T>::Output(ostream& out) const
{// Insert the chain elements into the stream out.
   if (!last) return;
   DoubleNode<T> *current;
   for (current = last->right; current != last;
                         current = current->right)
      out << current->data << "  ";
  // output last node
  out << current->data << "  ";
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const DoubleCircular<T>& x)
   {x.Output(out); return out;}

#endif
