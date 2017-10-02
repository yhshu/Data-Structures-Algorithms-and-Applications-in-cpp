

// doubly-linked circular linked list with head node
// extended to include Reverse

#ifndef HDoubleCircular_
#define HDoubleCircular_

#include <iostream.h>
#include "dnode.h"
#include "xcept.h"
#include "swap.h"

template <class T> class HDoubleCircularIterator;

template<class T>
class HDoubleCircular {
   friend HDoubleCircularIterator<T>;
   public:
      HDoubleCircular() {head = new DoubleNode<T>;
                         head->right = head;
                         head->left = head;}
      ~HDoubleCircular();
      bool IsEmpty() const {return head->right == head;}
      int Length() const; 
      bool Find(int k, T& x) const; 
      int Search(const T& x) const; 
      HDoubleCircular<T>& Delete(int k, T& x); 
      HDoubleCircular<T>& Insert(int k, const T& x);
      void Output(ostream& out) const;
      HDoubleCircular<T>& Reverse();
   private:
      DoubleNode<T> *head;  // pointer to head node
};

template<class T>
HDoubleCircular<T>::~HDoubleCircular()
{// HDoubleCircular destructor. Delete all nodes.
   // delete all nodes
   DoubleNode<T> *current = head->right,
                            // current node
                 *next;     // next node
   while (current != head) {
      next = current->right;
      delete current;
      current = next;
      }
   delete head;
}

template<class T>
int HDoubleCircular<T>::Length() const
{// Return the number of elements in the list.

   // count nodes
   DoubleNode<T> *current = head->right;
   int len = 0;
   while (current != head) {
     len++;
     current = current->right;
     }
   return len;
}

template<class T>
bool HDoubleCircular<T>::Find(int k, T& x) const
{// Set x to the k'th element in the list.
 // Return false if no k'th; return true otherwise.
   if (k < 1 || head->right == head) return false;

   DoubleNode<T> *current = head->right;
   int index = 1;  // index of current
   while (index < k && current != head) {
      // move to next node
      current = current->right;
      index++;
      }
   if (index == k) {x = current->data;
                    return true;}
   return false; // no k'th element
}

template<class T>
int HDoubleCircular<T>::Search(const T& x) const
{// Locate x.  Return position of x if found.
 // Return 0 if x not in the chain.

   // put x in head node to terminate search
   head->data = x;

   // examine nodes
   DoubleNode<T> *current = head->right;
   int index = 1;  // index of current
   while (current->data != x) {
      // move to next node
      current = current->right;
      index++;
      }
   if (current == head) return 0;
   return index;
}

template<class T>
HDoubleCircular<T>& HDoubleCircular<T>::Delete(int k, T& x)
{// Set x to the k'th element and delete it.
 // Throw OutOfBounds exception if no k'th element.
   if (k < 1 || head->right == head)
      throw OutOfBounds(); // no k'th
   
   // p will eventually point to k'th node
   DoubleNode<T> *p = head->right;
   int index = 1;  // index of p

   // move p to k'th
   for (; index < k && p != head; index++)
      p = p->right;

   // make sure p is at the k'th element
   if (index != k) throw OutOfBounds(); // no k'th

   // remove p from list
   p->right->left = p->left;
   p->left->right = p->right;

   // save k'th element and free node p
   x = p->data;
   delete p;

   return *this;
}

template<class T>
HDoubleCircular<T>& HDoubleCircular<T>::Insert(int k, const T& x)
{// Insert x after the k'th element.
 // Throw OutOfBounds exception if no k'th element.
 // Pass NoMem exception if inadequate space.
   if (k < 0) throw OutOfBounds();

   // p will eventually point to k'th node
   DoubleNode<T> *p = head;
   int index = 0;
   for (; index < k && p->right != head;
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

   return *this;
}

template<class T>
void HDoubleCircular<T>::Output(ostream& out) const
{// Insert the chain elements into the stream out.
   DoubleNode<T> *current;
   for (current = head->right; current != head;
                         current = current->right)
      out << current->data << "  ";
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const HDoubleCircular<T>& x)
   {x.Output(out); return out;}

template<class T>
HDoubleCircular<T>& HDoubleCircular<T>::Reverse()
{// In-pace reversal of the doubly linked circular list.
   // reverse the list by swapping left and right
   // pointers in all nodes
   DoubleNode<T> *current = head->right;
                            // current node
   while (current != head) {
      // swap pointers
      Swap(current->left, current->right);

      // move to next node
      current = current->left;
      }
   // swap head node pointers
   Swap(head->left, head->right);

   return *this;
}

#endif
