

// file lower.h
#ifndef Lower_
#define Lower_
#include<stdlib.h>
#include<iostream.h>

template <class type> class UpperMatrix;

template<class type>
class LowerMatrix {
friend UpperMatrix<type>;
public:
   LowerMatrix(int size = 10); // constructor
   ~LowerMatrix() {delete [] t;} // destructor
   void Store(const type& x, int i, int j);
   type Retrieve(int i, int j);
   int Add(const LowerMatrix<type>& A,
           const LowerMatrix<type>& B);
private:
   int n; //dimension
   type *t;
};

template<class type>
LowerMatrix<type>::LowerMatrix(int size)
{
n = size;
t = new type[n*(n+1)/2];
if (!t) { cerr << "Out Of Memory" << endl;
          exit(1);}
}

template<class type>
void LowerMatrix<type>::
          Store(const type& x, int i, int j)
{
// Store x as L(i,j).
if(i > n || j > n ) {
  cerr << "Improper storage location" << endl;
  exit(1);
}
if (i >= j) t[i*(i-1)/2+j-1] = x;
else if (x != 0) {
  cerr << "Element must be zero" << endl;
  exit(1);
    }
}
   
template <class type>
type LowerMatrix<type>::Retrieve(int i, int j)
{
// Retrieve L(i,j).
if( i > n || j > n) {
  cerr << "Improper retrieval location" << endl;
  exit(1);
       }
if (i >= j) return t[i*(i-1)/2+j-1];
else return 0;
}

template <class type>
int LowerMatrix<type>::Add(const LowerMatrix<type>& A,
                            const LowerMatrix<type>& B)
{
if (A.n != B.n || A.n != n) return 0;
for (int i = 0; i < n*(n+1)/2; i++)
   t[i] = A.t[i] + B.t[i];
return 1;
}
#endif
