// file ihash.h
#ifndef IdealHashTable_
#define IdealHashTable_

#include<iostream.h>
#include<stdlib.h>
#include "xcept.h"

template <class E>
class IdealHashTable {
public:
   IdealHashTable(int maxKey, int maxN); 
   ~IdealHashTable() {delete [] ht;
                      delete [] ele;}
   bool Search(int k, E& e);
   IdealHashTable<E>& Insert(const E& e);
   IdealHashTable<E>& Delete(int k, E& e);
   void Output();
private:
   E *ele;      // array of elements
   int *ht,     // hash table
       MaxKey,  // largest allowable key
       MaxN,    // max number of elements
       LastE;   // last used position of ele[]
};

template<class E>
IdealHashTable<E>::IdealHashTable(int maxKey, int maxN)
{// Create a hash table ht with maxKey + 1 buckets
 // and an array ele[] with capacity maxN.
   MaxKey = maxKey;
   MaxN = maxN;
   ht = new int [MaxKey+1];
   ele = new E [MaxN];
   LastE = -1; // last used spot in ele[]
}

template<class E>
bool IdealHashTable<E>::Search(int k, E& e)
{// Put element with key k into e.
 // Return false if there is no element with key k.
   if (k < 0 || k > MaxKey)
      return false; // key out of range
   
   if (ht[k] < 0 || ht[k] > LastE || ele[ht[k]] != k)
      return false; // key not in table
   
   e = ele[ht[k]];
   return true;
}

template<class E>
IdealHashTable<E>& IdealHashTable<E>::
                   Insert(const E& e)
{// Insert e into the table.  Throw an exception
 // if the key is out of range, a duplicate,
 // or if there is no space.
   int k = e; // extract key
   if (k < 0 || k > MaxKey)
      throw BadInput(); // key out of range

   E x;
   if (Search(k,x))
      throw BadInput(); // duplicate

   if (LastE == MaxN - 1)
      throw NoMem();    // no space

   // put e into the table
   ele[++LastE] = e;    // put in element
   ht[k] = LastE;       // set index to element

   return *this;
}

template<class E>
IdealHashTable<E>& IdealHashTable<E>::
                   Delete(int k, E& e)
{// Delete element with key k.
 // Put deleted element into e.
 // Throw BadInput if no matching element.
   if (!Search(k,e))
      throw BadInput(); // no matching element
   
   // delete from table and fill vacancy with
   // last element in ele[]
   ele[ht[k]] = ele[LastE--]; // relocate last
                              // element to vacancy
   int key = ele[ht[k]]; // key of moved element
   ht[key] = ht[k]; // new location of moved element

   return *this;
}

template<class E>
void IdealHashTable<E>::Output()
{
   for (int i = 0; i <= LastE; i++)
      cout << ele[i] << endl;
}

#endif
