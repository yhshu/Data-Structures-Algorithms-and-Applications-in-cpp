// first backtracking code to load containers on to two ships
// code finds weight of best loading for first ship only

#include<iostream.h>

template<class T>
class Loading {
   friend MaxLoading(T [], T, int);
   private:
      void maxLoading(int i);
      int n;    // number of containers
      T *w,     // container weight array
        c,      // capacity of first ship
        cw,     // weight of current loading
        bestw;  // weight of best loading so far
};

template<class T>
void Loading<T>::maxLoading(int i)
{// Search from level i node.
   if (i > n) {// at a leaf
      if (cw > bestw) bestw = cw;
      return;}
   // check subtrees
   if (cw + w[i] <= c) {// try x[i] = 1
      cw += w[i];
      maxLoading(i+1);
      cw -= w[i];}
   maxLoading(i+1);// try x[i] = 0
}

template<class T>
T MaxLoading(T w[], T c, int n)
{// Return weight of best loading.
   Loading<T> X;
   // initialize X
   X.w = w;
   X.c = c;
   X.n = n;
   X.bestw = 0;
   X.cw = 0;

   // compute weight of best loading
   X.maxLoading(1);
   return X.bestw;
}

void main(void)
{
   int w[6] = {0, 7, 2, 6, 5, 4};
   int n = 5;
   int c = 10;
   cout << "Value of max loading is" << endl;
   cout << MaxLoading(w,c,n) << endl;
}
