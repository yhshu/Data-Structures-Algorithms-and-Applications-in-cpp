
// sorted chain with head and tail nodes

#ifndef SortedChain_
#define SortedChain_

#include "sonode.h"
#include "xcept.h"


template<class E, class K>
class SortedChain {
   public:
      SortedChain();
      ~SortedChain();
      bool IsEmpty() const
           {return head->link == tail;}
      int Length() const;
      bool Search(const K& k, E& e) const;
      SortedChain<E,K>& Delete(const K& k, E& e);
      SortedChain<E,K>& Insert(const E& e);
      SortedChain<E,K>& DistinctInsert(const E& e);
      void Output(ostream& out) const;
   private:
      SortedChainNode<E,K> *head,  // pointer to head node
                           *tail;  // pointer to tail node
};

template<class E, class K>
SortedChain<E,K>::SortedChain()
{// Constructor.  Allocate and link
 // head and tail nodes.
   head = new SortedChainNode<E,K>;
   tail = new SortedChainNode<E,K>;
   head->link = tail;
   // no need to set tail->link to 0
}

template<class E, class K>
SortedChain<E,K>::~SortedChain()
{// Destructor.  Delete all nodes.
   SortedChainNode<E,K> *next;
   while (head != tail) {
      next = head->link;
      delete head;
      head = next;
      }
   delete tail;
}

template<class E, class K>
int SortedChain<E,K>::Length() const
{// Size of list.
   SortedChainNode<E,K> *p = head->link;
   int len = 0;
   while (p != tail) {
      len++;
      p = p->link;
      }
   return len;
}

template<class E, class K>
bool SortedChain<E,K>::
     Search(const K& k, E& e) const
{// Put element that matches k in e.
 // Return false if no match.

   // first put k in the tail node
   tail->data = k;

   // now search the chain
   SortedChainNode<E,K> *p = head->link;
   
   // search for match with k
   while (p->data < k)
      p = p->link;

   // verify match
   if (p != tail && p->data == k) // yes, found match
      {e = p->data; return true;}
   return false; // no match
}

template<class E, class K>
SortedChain<E,K>& SortedChain<E,K>::
                  Delete(const K& k, E& e)
{// Delete element that matches k.
 // Put deleted element in e.
 // Throw BadInput exception if no match.

   // first put k in tail
   tail->data = k;

   // now search for matching element
   SortedChainNode<E,K> *p = head->link,
                        *tp = head; // trail p
   
   // search for match with k
   while (p->data < k) {
      tp = p;
      p = p->link;
      }

   // verify match
   if (p != tail && p->data == k) {// found a match
           e = p->data;    // save data

           // remove p from chain
           tp->link = p->link;

           delete p;
           return *this;}
   throw BadInput();  // no match
   return *this;
}

template<class E, class K>
SortedChain<E,K>& SortedChain<E,K>::
                  Insert(const E& e)
{// Insert e, throw an exception if no space.

   // first put e in tail
   tail->data = e;

   // now search for insertion point
   SortedChainNode<E,K> *p = head->link,
                        *tp = head; // trail p

   // move tp so that e can be inserted after tp
   while (p->data < e) {
      tp = p;
      p = p->link;
      }

   // setup a new node *q for e
   SortedChainNode<E,K> *q = new SortedChainNode<E,K>;
   q->data = e;

   // insert node between tp and p
   q->link = p;
   tp->link = q;

   return *this;
}

template<class E, class K>
SortedChain<E,K>& SortedChain<E,K>
                 ::DistinctInsert(const E& e)
{// Insert e only if no element with same key
 // currently in list.
 // Throw BadInput exception if duplicate.

   // first put e in tail
   tail->data = e;

   // now search for insertion point
   SortedChainNode<E,K> *p = head->link,
                        *tp = head; // trail p

   // move tp so that e can be inserted after tp
   while (p->data < e) {
      tp = p;
      p = p->link;
      }

   // check if duplicate
   if (p != tail && p->data == e) throw BadInput();

   // not duplicate, set up node for e
   SortedChainNode<E,K> *q = new SortedChainNode<E,K>;
   q->data = e;

   // insert node between tp and p
   q->link = p;
   tp->link = q;

   return *this;
}

template<class E, class K>
void SortedChain<E,K>::Output(ostream& out) const
{// Insert the chain elements into the stream out.
   SortedChainNode<E,K> *p;
   for (p = head->link; p != tail; p = p->link)
      out << p->data << "  ";
}

// overload <<
template <class E, class K>
ostream& operator<<(ostream& out,
                    const SortedChain<E,K>& x)
   {x.Output(out); return out;}

#endif
