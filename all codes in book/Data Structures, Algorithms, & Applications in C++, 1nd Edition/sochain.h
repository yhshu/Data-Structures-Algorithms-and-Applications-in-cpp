// file sochain.h

// sorted chain

#ifndef SortedChain_
#define SortedChain_

#include "sonode.h"
#include "xcept.h"

template<class E, class K>
class SortedChain {
   public:
      SortedChain() {first = 0;}
      ~SortedChain();
      bool IsEmpty() const {return first == 0;}
      int Length() const;
      bool Search(const K& k, E& e) const;
      SortedChain<E,K>& Delete(const K& k, E& e);
      SortedChain<E,K>& Insert(const E& e);
      SortedChain<E,K>& DistinctInsert(const E& e);
      void Output(ostream& out) const;
   private:
      SortedChainNode<E,K> *first;  // pointer to first node
};

template<class E, class K>
SortedChain<E,K>::~SortedChain()
{// Destructor.  Delete all nodes.
   SortedChainNode<E,K> *next;
   while (first) {
      next = first->link;
      delete first;
      first = next;
      }
}

template<class E, class K>
int SortedChain<E,K>::Length() const
{// Size of list.
   SortedChainNode<E,K> *p = first;
   int len = 0;
   while (p) {
      len++;
      p = p->link;
      }
   return len;
}

template<class E, class K>
bool SortedChain<E,K>::Search(const K& k, E& e) const
{// Put element that matches k in e.
 // Return false if no match.

   SortedChainNode<E,K> *p = first;
   
   // search for match with k
   while (p && p->data < k)
      p = p->link;

   // verify match
   if (p && p->data == k) // yes, found match
      {e = p->data; return true;}
   return false; // no match
}

template<class E, class K>
SortedChain<E,K>& SortedChain<E,K>
                  ::Delete(const K& k, E& e)
{// Delete element that matches k.
 // Put deleted element in e.
 // Throw BadInput exception if no match.

   SortedChainNode<E,K> *p = first,
                        *tp = 0; // trail p
   
   // search for match with k
   while (p && p->data < k) {
      tp = p;
      p = p->link;
      }

   // verify match
   if (p && p->data == k) {// found a match
           e = p->data;    // save data

           // remove p from chain
           if (tp) tp->link = p->link;
           else first = p->link;  // p is first node

           delete p;
           return *this;}
   throw BadInput();  // no match
   return *this;      // Visual C++ needs this line
}

template<class E, class K>
SortedChain<E,K>& SortedChain<E,K>::Insert(const E& e)
{// Insert e, throw an exception if no space.

   SortedChainNode<E,K> *p = first,
                        *tp = 0; // trail p

   // move tp so that e can be inserted after tp
   while (p && p->data < e) {
      tp = p;
      p = p->link;
      }

   // setup a new node *q for e
   SortedChainNode<E,K> *q = new SortedChainNode<E,K>;
   q->data = e;

   // insert node just after tp
   q->link = p;
   if (tp) tp->link = q;
   else first = q;

   return *this;
}

template<class E, class K>
SortedChain<E,K>& SortedChain<E,K>
                 ::DistinctInsert(const E& e)
{// Insert e only if no element with same key
 // currently in list.
 // Throw BadInput exception if duplicate.

   SortedChainNode<E,K> *p = first,
                        *tp = 0; // trail p

   // move tp so that e can be inserted after tp
   while (p && p->data < e) {
      tp = p;
      p = p->link;
      }

   // check if duplicate
   if (p && p->data == e) throw BadInput();

   // not duplicate, set up node for e
   SortedChainNode<E,K> *q = new SortedChainNode<E,K>;
   q->data = e;

   // insert node just after tp
   q->link = p;
   if (tp) tp->link = q;
   else first = q;

   return *this;
}

template<class E, class K>
void SortedChain<E,K>::Output(ostream& out) const
{// Insert the chain elements into the stream out.
   SortedChainNode<E,K> *p;
   for (p = first; p; p = p->link)
      out << p->data << "  ";
}

// overload <<
template <class E, class K>
ostream& operator<<(ostream& out,
                    const SortedChain<E,K>& x)
   {x.Output(out); return out;}

#endif
