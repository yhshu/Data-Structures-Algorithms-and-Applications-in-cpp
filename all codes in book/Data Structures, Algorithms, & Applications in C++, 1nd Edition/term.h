#ifndef Term_
#define Term_

template <class T> class SparseMatrix;

template <class T>
class Term {
   friend SparseMatrix<T>;
   friend ostream& operator<<
          (ostream&, const SparseMatrix<T>&);
   friend istream& operator>>
          (istream&, SparseMatrix<T>&);
   private:
      int row, col;
      T value;
};

#endif
