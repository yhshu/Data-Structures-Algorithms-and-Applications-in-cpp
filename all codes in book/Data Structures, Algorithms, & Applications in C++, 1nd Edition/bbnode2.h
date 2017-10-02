// used by bbknap.cpp

#ifndef bbnode_
#define bbnode_

template <class Tw, class Tp> class Knap;

class bbnode {
   friend Knap<int,int>;
   friend int Knapsack(int *, int *, int, int, int *);
   private:
      bbnode *parent;  // pointer to parent node
      bool LChild;     // true iff left child of parent
};

template<class Tw, class Tp>
class  HeapNode {
   friend Knap<Tw,Tp>;
   public:
      operator Tp () const {return uprofit;}
   private:
      Tp uprofit,   // upper profit of live node
         profit;    // profit of partial filling
      Tw weight;    // weight of partial filling
      int level;    // level of live node
      bbnode *ptr;  // pointer to live node
};

#endif
