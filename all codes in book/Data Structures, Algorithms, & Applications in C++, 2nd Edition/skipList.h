// skip list data structure, implements dictionary

#ifndef skipList_
#define skipList_



#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include "dictionary.h"
#include "skipNode.h"
#include "myExceptions.h"

using namespace std;

template<class K, class E>
class skipList : public dictionary<K,E> 
{
   public:
      skipList(K, int maxPairs = 10000, float prob = 0.5);
      ~skipList();

      bool empty() const {return dSize == 0;}
      int size() const {return dSize;}
      pair<const K, E>* find(const K&) const;
      void erase(const K&);
      void insert(const pair<const K, E>&);
      void output(ostream& out) const;

   protected:
      float cutOff;          // used to decide level number
      int level() const;     // generate a random level number
      int levels;            // max current nonempty chain
      int dSize;             // number of pairs in dictionary
      int maxLevel;          // max permissible chain level
      K tailKey;             // a large key
      skipNode<K,E>* search(const K&) const;
                             // search saving last nodes seen
      skipNode<K,E>* headerNode;  // header node pointer
      skipNode<K,E>* tailNode;    // tail node pointer
      skipNode<K,E>** last;       // last[i] = last node seen on level i
};

template<class K, class E>
skipList<K,E>::skipList(K largeKey, int maxPairs, float prob)
{// Constructor for skip lists with keys smaller than largeKey and
 // size at most maxPairs. 0 < prob < 1.
   cutOff = prob * RAND_MAX;
   maxLevel = (int) ceil(logf((float) maxPairs) / logf(1/prob)) - 1;
   levels = 0;  // initial number of levels
   dSize = 0;
   tailKey = largeKey;

   // create header & tail nodes and last array
   pair<K,E> tailPair;
   tailPair.first = tailKey;
   headerNode = new skipNode<K,E> (tailPair, maxLevel + 1);
   tailNode = new skipNode<K,E> (tailPair, 0);
   last = new skipNode<K,E> *[maxLevel+1];

   // header points to tail at all levels as lists are empty
   for (int i = 0; i <= maxLevel; i++)
       headerNode->next[i] = tailNode;
}

template<class K, class E>
skipList<K,E>::~skipList()
{// Delete all nodes and array last.
   skipNode<K,E> *nextNode;

   // delete all nodes by following level 0 chain
   while (headerNode != tailNode)
   {
      nextNode = headerNode->next[0];
      delete headerNode;
      headerNode = nextNode;
   }
   delete tailNode;

   delete [] last;
}

template<class K, class E>
pair<const K,E>* skipList<K,E>::find(const K& theKey) const
{// Return pointer to matching pair.
 // Return NULL if no matching pair.
   if (theKey >= tailKey)
      return NULL;  // no matching pair possible

   // position beforeNode just before possible node with theKey
   skipNode<K,E>* beforeNode = headerNode;
   for (int i = levels; i >= 0; i--)          // go down levels
      // follow level i pointers
      while (beforeNode->next[i]->element.first < theKey)
         beforeNode = beforeNode->next[i];

   // check if next node has theKey
   if (beforeNode->next[0]->element.first == theKey)
      return &beforeNode->next[0]->element; 

   return NULL;  // no matching pair
}

template<class K, class E>
int skipList<K,E>::level() const
{// Return a random level number <= maxLevel.
   int lev = 0;
   while (rand() <= cutOff)
      lev++;
   return (lev <= maxLevel) ? lev : maxLevel;
}

template<class K, class E>
skipNode<K,E>* skipList<K,E>::search(const K& theKey) const
{// Search for theKey saving last nodes seen at each
 // level in the array last
 // Return node that might contain theKey.
   // position beforeNode just before possible node with theKey
   skipNode<K,E>* beforeNode = headerNode;
   for (int i = levels; i >= 0; i--)
   {
      while (beforeNode->next[i]->element.first < theKey)
         beforeNode = beforeNode->next[i];
      last[i] = beforeNode;  // last level i node seen
   }
   return beforeNode->next[0];
}

template<class K, class E>
void skipList<K,E>::insert(const pair<const K, E>& thePair)
{// Insert thePair into the dictionary. Overwrite existing
 // pair, if any, with same key.
   if (thePair.first >= tailKey) // key too large
   {ostringstream s;
    s << "Key = " << thePair.first << " Must be < " << tailKey;
    throw illegalParameterValue(s.str());
   }
   
   // see if pair with theKey already present
   skipNode<K,E>* theNode = search(thePair.first);
   if (theNode->element.first == thePair.first)
   {// update theNode->element.second
      theNode->element.second = thePair.second;
      return;
   }

   // not present, determine level for new node
   int theLevel = level(); // level of new node
   // fix theLevel to be <= levels + 1
   if (theLevel > levels)
   {
      theLevel = ++levels;
      last[theLevel] = headerNode;
   }

   // get and insert new node just after theNode
   skipNode<K,E>* newNode = new skipNode<K,E>(thePair, theLevel + 1);
   for (int i = 0; i <= theLevel; i++)
   {// insert into level i chain
      newNode->next[i] = last[i]->next[i];
      last[i]->next[i] = newNode;
   }

   dSize++;
   return;
}

template<class K, class E>
void skipList<K,E>::erase(const K& theKey)
{// Delete the pair, if any, whose key equals theKey.
   if (theKey >= tailKey) // too large
      return;

   // see if matching pair present
   skipNode<K,E>* theNode = search(theKey);
   if (theNode->element.first != theKey) // not present
      return;

   // delete node from skip list
   for (int i = 0; i <= levels &&
                   last[i]->next[i] == theNode; i++)
      last[i]->next[i] = theNode->next[i];
   
   // update levels
   while (levels > 0 && headerNode->next[levels] == tailNode)
      levels--;
   
      delete theNode;
      dSize--;
}

template<class K, class E>
void skipList<K,E>::output(ostream& out) const
{// Insert the dictionary pairs into the stream out.
   // follow level 0 chain
   for (skipNode<K,E>* currentNode = headerNode->next[0];
                       currentNode != tailNode;
                       currentNode = currentNode->next[0])
      out << currentNode->element.first << " "
          << currentNode->element.second << "  ";
}

// overload <<
template <class K, class E>
ostream& operator<<(ostream& out, const skipList<K,E>& x)
   {x.output(out); return out;}

#endif
