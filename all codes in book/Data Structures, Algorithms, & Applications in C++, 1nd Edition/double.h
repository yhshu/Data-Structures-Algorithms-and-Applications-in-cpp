
// file double.h
#ifndef Double_
#define Double_
#include <stdlib.h>
#include <iostream.h>
#include "dnode.h"
#include "xcept.h"

template<class T>
class Double {
   public:
      Double() {LeftEnd = RightEnd = 0;}; 
      ~Double(); 
      int Length() const; 
      bool Find(int k, T& x) const; 
      int Search(const T& x) const; 
      Double<T>& Delete(int k, T& x); 
      Double<T>& Insert(int k, const T& x); 
      void Output(ostream& out) const;
   private:
      DoubleNode<T> *LeftEnd, *RightEnd;
};

#endif
