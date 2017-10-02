
// file hash.h
#ifndef HashTable_
#define HashTable_

#include <iostream.h>
#include <stdlib.h>
#include "xcept.h"

template<class E, class K>
class HashTable {
   public:
      HashTable(int divisor = 11); 
      ~HashTable() {delete [] ht;
                    delete [] empty;}
      bool Search(const K& k, E& e) const;
      HashTable<E,K>& Insert(const E& e);
      void Output();// output the hash table
   private:
      int hSearch(const K& k) const;
      int D; // hash function divisor
      E *ht; // hash table array
      bool *empty; // 1D array
};

template<class E, class K>
HashTable<E,K>::HashTable(int divisor)
{// Constructor.
   D = divisor;

   // allocate hash table arrays
   ht = new E [D];
   empty = new bool [D];

   // set all buckets to empty
   for (int i = 0; i < D; i++)
      empty[i] = true;
}

template<class E, class K>
int HashTable<E,K>::hSearch(const K& k) const
{// Search an open addressed table.
 // Return location of k if present.
 // Otherwise return insert point if there is space.
   int i = k % D; // home bucket
   int j = i;     // start at home bucket
   do {
      if (empty[j] || ht[j] == k) return j;
      j = (j + 1) % D;  // next bucket
      } while (j != i); // returned to home?

   return j;  // table full
}

template<class E, class K>
bool HashTable<E,K>::Search(const K& k, E& e) const
{// Put element that matches k in e.
 // Return false if no match.
   int b = hSearch(k);
   if (empty[b] || ht[b] != k) return false;
   e = ht[b];
   return true;
}

template<class E, class K>
HashTable<E,K>& HashTable<E,K>::Insert(const E& e)
{// Hash table insert.
   K k = e; // extract key
   int b = hSearch(k);

   // check if insert is to be done
   if (empty[b]) {empty[b] = false;
                  ht[b] = e;
                  return *this;}
  
   // no insert, check if duplicate or full
   if (ht[b] == k) throw BadInput(); // duplicate
   throw NoMem(); // table full
   return *this;  // Visual C++ needs this line
}

template<class E, class K>
void HashTable<E,K>::Output()
{
   for (int i = 0; i< D; i++) {
      if (empty[i]) cout << "empty" << endl;
      else cout << ht[i] << endl;}
}

#endif
