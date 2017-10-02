
// file Chash.h
#ifndef ChainedHashTable_
#define ChainedHashTable_

#include "sochain.h" // sorted chain
#include <iostream.h>

template<class etype, class ktype>
class ChainHashTable {
   public:
      ChainHashTable(int divisor = 11); // constructor
      ~ChainHashTable() {delete [] ht;}
      int Search(ktype k, etype& e)
          {e.key = k; return ht[k % D].Search(e);}
      int Insert(etype e)
          {return ht[e.key % D].DistinctInsert(e);}
      int Delete(ktype k, etype& e)
          {e.key = k; return ht[k % D].Delete(e);}
      void Print();
   private:
      int D;
      SortedChain<etype> *ht;
};

template<class etype, class ktype>
ChainHashTable<etype, ktype>::ChainHashTable(int divisor)
{
   D = divisor;
   ht = new SortedChain<etype> [D];
   if (!ht)
    {cerr << "Out of memory" << endl;
     exit(1);}
}

template<class etype, class ktype>
void ChainHashTable<etype, ktype>::Print()
{
   for (int i = 0; i < D; i++) {
     cout << "Chain " << i << ' ';
     ht[i].Print();}
}

#endif
