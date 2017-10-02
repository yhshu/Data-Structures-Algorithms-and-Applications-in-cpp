// file Chash.h
#ifndef ChainedHashTable_
#define ChainedHashTable_

#include <iostream.h>
#include <stdlib.h>
#include "sochain.h" // sorted chain

template<class E, class K>
class ChainHashTable {
   public:
      ChainHashTable(int divisor = 11)
         {D = divisor;
          ht = new SortedChain<E,K> [D];}
      ~ChainHashTable() {delete [] ht;}
      bool Search(const K& k, E& e) const
           {return ht[k % D].Search(k, e);}
      ChainHashTable<E,K>& Insert(const E& e)
           {ht[e % D].DistinctInsert(e);
            return *this;}
      ChainHashTable<E,K>& Delete(const K& k, E& e)
           {ht[k % D].Delete(k, e);
            return *this;}
      void Output() const;   // output the table
   private:
      int D;                 // divisor
      SortedChain<E,K> *ht;  // array of chains
};

template<class E, class K>
void ChainHashTable<E,K>::Output() const
{
   SortedChain<E,K> c;
   for (int i = 0; i < D; i++) {
     cout << "Chain " << i << ' ';
     ht[i].Output(cout);
     cout << endl;}
}

#endif
