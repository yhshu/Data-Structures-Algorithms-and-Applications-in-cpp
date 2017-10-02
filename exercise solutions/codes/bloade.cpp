
// loading containers on to two ships via backtracking
// code finds best loading of first ship as well as its weight
// this is done by first finding the weight of the best loading
// and then determining the containers to load

#include<iostream.h>

template<class T>
class Loading {
   friend MaxLoading(T [], T, int, int []);
   private:
      void maxLoading1(int i);
      bool maxLoading2(int i);
      int n,      // number of containers
          *bestx; // best solution
      T *w,       // container weight array
        c,        // ship capacity
        cw,       // weight of current loading
        bestw,    // weight of best loading so far
        r;        // sum of remaining container weights
};

template<class T>
void Loading<T>::maxLoading1(int i)
{// Search from level i node to find weight
 // of best loading.
   if (i > n) {// at a leaf
      bestw = cw;
      return;}
   // check subtrees
   r -= w[i];
   if (cw + w[i] <= c) {// try x[i] = 1
      cw += w[i];
      maxLoading1(i+1);
      cw -= w[i];}
   if (cw + r > bestw) // try x[i] = 0
      maxLoading1(i+1);
   r += w[i];
}

template<class T>
bool Loading<T>::maxLoading2(int i)
{// Search from level i node for a loading with
 // weight bestw.  Return true when this loading has
 // been found.
   if (i > n) // at a leaf
      // this leaf has best loading
      return true;
   // check subtrees
   r -= w[i];
   if (cw + w[i] <= c) {// try x[i] = 1
      cw += w[i];
      if (maxLoading2(i+1)) {// found best loading
         bestx[i] = 1;
         return true;
         }
      cw -= w[i];}
   if (cw + r >= bestw) // try x[i] = 0
      if (maxLoading2(i+1)) {// found best loading
         bestx[i] = 0;
         return true;
         }
   r += w[i];
   return false;
}

template<class T>
T MaxLoading(T w[], T c, int n, int bestx[])
{// Return best loading and its value.
   Loading<T> X;
   // initialize X
   X.w = w;
   X.c = c;
   X.n = n;
   X.bestx = bestx;
   X.bestw = 0;
   X.cw = 0;
   // initial r is sum of all weights
   X.r = 0;
   for (int i = 1; i <= n; i++) 
      X.r += w[i];

   // compute weight of best loading
   X.maxLoading1(1);

   // determine the best loading
   X.maxLoading2(1);

   return X.bestw;
}



void main(void)
{
   int w[6] = {0, 2, 2, 4, 5, 6};
   int x[6];
   int n = 5;
   int c = 10;
   cout << "Value of max loading is" << endl;
   cout << MaxLoading(w,c,n,x) << endl;
   cout << "x values are" << endl;
   for (int i=1; i<=n; i++)
      cout << x[i] << ' ';
   cout << endl;
}
