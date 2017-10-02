

// doubly linked list

#ifndef Double_
#define Double_


#include <iostream.h>
#include "dnode.h"
#include "xcept.h"

template<class T>
class Double {
   public:
      Double() {LeftEnd = RightEnd = 0;}
      ~Double();
      bool IsEmpty() const {return LeftEnd == 0;}
      int Length() const; 
      bool Find(int k, T& x) const; 
      int Search(const T& x) const; 
      Double<T>& Delete(int k, T& x); 
      Double<T>& Insert(int k, const T& x);
      void Output(ostream& out) const;
   private:
      DoubleNode<T> *LeftEnd,   // pointer to leftmost node
                    *RightEnd;  // pointer to rightmost node
};

template<class T>
Double<T>::~Double()
{// Double destructor. Delete all nodes.
   DoubleNode<T> *curr = LeftEnd,  // current node
                 *next;            // next node
   while (curr) {
      next = curr->right;
      delete curr;
      curr = next;
      }
}

template<class T>
int Double<T>::Length() const
{// Return the number of elements in the list.
   // count nodes
   DoubleNode<T> *curr = LeftEnd;
   int len = 0;  // number to left of curr
   while (curr) {
     len++;
     curr = curr->right;
     }
   return len;
}

template<class T>
bool Double<T>::Find(int k, T& x) const
{// Set x to the k'th element in the list.
 // Return false if no k'th; return true otherwise.
   if (k < 1 || !LeftEnd) return false;

   DoubleNode<T> *curr = LeftEnd;
   int index = 1;  // index of curr
   while (index < k && curr) {
      // move to next node
      curr = curr->right;
      index++;
      }
   if (index == k) {x = curr->data;
                    return true;}
   return false; // no k'th element
}

template<class T>
int Double<T>::Search(const T& x) const
{// Locate x.  Return position of x if found.
 // Return 0 if x not in the chain.
   if (!LeftEnd) return 0;  // list is empty

   // examine nodes
   DoubleNode<T> *curr = LeftEnd;
   int index = 1;  // index of curr
   while (curr && curr->data != x) {
      // move to next node
      curr = curr->right;
      index++;
      }
   if (curr) return index;
   return 0;
}

template<class T>
Double<T>& Double<T>::Delete(int k, T& x)
{// Set x to the k'th element and delete it.
 // Throw OutOfBounds exception if no k'th element.
   if (k < 1 || !LeftEnd)
      throw OutOfBounds(); // no k'th
   
   // p will eventually point to k'th node
   DoubleNode<T> *p = LeftEnd;
   int index = 1;  // index of p

   // move p to k'th
   for (; index < k && p; index++)
      p = p->right;

   // make sure p is at the k'th element
   if (index != k) throw OutOfBounds(); // no k'th

   // remove p from list
   if (p == LeftEnd) {
      // delete first node
      LeftEnd = LeftEnd->right;
      if (!LeftEnd)  // list is empty
         RightEnd = 0;
      else  // list is not empty
         LeftEnd->left = 0;
      }
   else if (p == RightEnd) {
           // delete last node
           RightEnd = RightEnd->left;
           RightEnd->right = 0;
           }
         else {
            // delete an interior node
            p->right->left = p->left;
            p->left->right = p->right;
            }

   // save k'th element and free node p
   x = p->data;
   delete p;

   return *this;
}

template<class T>
Double<T>& Double<T>::Insert(int k, const T& x)
{// Insert x after the k'th element.
 // Throw OutOfBounds exception if no k'th element.
 // Pass NoMem exception if inadequate space.
   if (k < 0) throw OutOfBounds();

   if (k) {// locate k'th node
      if (!LeftEnd) throw OutOfBounds();  // empty list

      // p will eventually point to k'th node
      DoubleNode<T> *p = LeftEnd;
      int index = 1;
      // move p to k'th
      for (; index < k && p; index++)
         p = p->right;
      if (index != k) throw OutOfBounds(); // no k'th

      // insert after p
      DoubleNode<T> *y = new DoubleNode<T>;
      y->data = x;
      y->right = p->right;
      p->right = y;
      y->left = p;
      if (p == RightEnd) // y is now the last node
         RightEnd = y;
      else  // y is not the last node
         y->right->left = y;
      }
   else {// insert as first element
         DoubleNode<T> *y = new DoubleNode<T>;
         y->data = x;
         if (LeftEnd) {// insert into nonempty list
            y->right = LeftEnd;
            y->left = 0;
            LeftEnd->left = y;
            }
         else {// insert into an empty list
               LeftEnd = RightEnd = y;
               y->left = y->right = 0;
               }
         LeftEnd = y;
         }

   return *this;
}

template<class T>
void Double<T>::Output(ostream& out) const
{// Insert the chain elements into the stream out.
   for (DoubleNode<T> *curr = LeftEnd;
        curr; curr = curr->right)
      out << curr->data << "  ";
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const Double<T>& x)
   {x.Output(out); return out;}

#endif
