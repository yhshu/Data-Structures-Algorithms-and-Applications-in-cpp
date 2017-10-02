// file skip.h

#ifndef SkipList_
#define SkipList_

#include <stdlib.h>
#include <iostream.h>
#include <math.h>
#include "xcept.h"
#include "skipnode.h"

template<class E, class K>
class SkipList {
   public:
      SkipList(K Large, int MaxE = 10000,
                        float p = 0.5);
      ~SkipList(); 
      bool Search(const K& k, E& e) const;
      SkipList<E,K>& Insert(const E& e);
      SkipList<E,K>& Delete(const K& k, E& e);
      void Output();
   private:
      int Level();
      SkipNode<E,K> *SaveSearch(const K& k);
      int MaxLevel;  // max permissible chain level
      int Levels;    // max current nonempty chain
      int CutOff;    // used to decide level number
      K TailKey;     // a large key
      SkipNode<E,K> *head;  // head node pointer
      SkipNode<E,K> *tail;  // tail node pointer
      SkipNode<E,K> **last; // array of pointers
};

template<class E, class K>
SkipList<E,K>::SkipList(K Large, int MaxE, float p)
{// Constructor.
   CutOff = p * RAND_MAX;
   MaxLevel = ceil(log(MaxE) / log(1/p)) - 1;
   TailKey = Large;
   Levels = 0;  // initial number of levels

   // create head & tail nodes and last array
   head = new SkipNode<E,K> (MaxLevel+1);
   tail = new SkipNode<E,K> (0);
   last = new SkipNode<E,K> *[MaxLevel+1];
   tail->data = Large;

   // head points to tail at all levels as empty
   for (int i = 0; i <= MaxLevel; i++)
       head->link[i] = tail;
}

template<class E, class K>
SkipList<E,K>::~SkipList()
{// Delete all nodes and array last.
   SkipNode<E,K> *next;

   // delete all nodes by deleting level 0
   while (head != tail) {
      next = head->link[0];
      delete head;
      head = next;
      }
   delete tail;

   delete [] last;
}

template<class E, class K>
bool SkipList<E,K>::Search(const K& k, E& e) const
{// Search for element that matches k.
 // Put matching element in e.
 // Return false if no match.
   if (k >= TailKey) return false;

   // position p just before possible node with k
   SkipNode<E,K> *p = head;
   for (int i = Levels; i >= 0; i--) // go down levels
      while (p->link[i]->data < k)   // follow level i
         p = p->link[i];             // pointers

   // check if next node has key k
   e = p->link[0]->data; 
   return (e == k);
}

template<class E, class K>
SkipNode<E,K> * SkipList<E,K>::SaveSearch(const K& k)
{// Search for k and save last position
 // visited at each level.
   // position p just before possible node with k
   SkipNode<E,K> *p = head;
   for (int i = Levels; i >= 0; i--) {
      while (p->link[i]->data < k)
         p = p->link[i];
      last[i] = p;  // last level i node seen
      }
   return (p->link[0]);
}

template<class E, class K>
int SkipList<E,K>::Level()
{// Generate a random level number <= MaxLevel.
   int lev = 0;
   while (rand() <= CutOff)
      lev++;
   return (lev <= MaxLevel) ? lev : MaxLevel;
}

template<class E, class K>
SkipList<E,K>& SkipList<E,K>::Insert(const E& e)
{// Insert e if not duplicate.
   K k = e; // extract key
   if (k >= TailKey) throw BadInput(); // too large
   
   // see if duplicate
   SkipNode<E,K> *p = SaveSearch(k);
   if (p->data == e) throw BadInput(); // duplicate

   // not duplicate, determine level for new node
   int lev = Level(); // level of new node
   // fix lev to be <= Levels + 1
   if (lev > Levels) {lev = ++Levels;
                      last[lev] = head;}

   // get and insert new node just after p
   SkipNode<E,K> *y = new SkipNode<E,K> (lev+1);
   y->data = e;
   for (int i = 0; i <= lev; i++) {
      // insert into level i chain
      y->link[i] = last[i]->link[i];
      last[i]->link[i] = y;
      }

   return *this;
}

template<class E, class K>
SkipList<E,K>& SkipList<E,K>::Delete(const K& k, E& e)
{// Delete element that matches k.  Put deleted
 // element in e.  Throw BadInput if no match.
   if (k >= TailKey) throw BadInput(); // too large

   // see if matching element present
   SkipNode<E,K> *p = SaveSearch(k);
   if (p->data != k) throw BadInput(); // not present

   // delete node from skip list
   for (int i = 0; i <= Levels &&
                      last[i]->link[i] == p; i++)
      last[i]->link[i] = p->link[i];
   
   // update Levels
   while (Levels > 0 && head->link[Levels] == tail)
      Levels--;
   
   e = p->data;
   delete p;
   return *this;
}

template<class E, class K>
void SkipList<E,K>::Output()
{
   SkipNode<E,K> *y = head->link[0];
   for (; y != tail; y = y->link[0])
      cout << y->data << ' ';
   cout << endl;
}

#endif
