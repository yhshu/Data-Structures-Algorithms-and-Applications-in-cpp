#ifndef MatrixNodes_
#define MatrixNodes_

// node types used by class LinkedMatrix

template <class T> class LinkedMatrix;

template<class T>
class CNode {
   friend LinkedMatrix<T>;
   friend ostream& operator<<
          (ostream&, const LinkedMatrix<T>&);
   friend istream& operator>>
          (istream&, LinkedMatrix<T>&);
   public:
      int operator !=(const CNode<T>& y)
         {return (value != y.value);}
      void Output(ostream& out) const
         {out << "column " << col 
              << " value " << value;}
   private:
      int col;
      T value;
};

template<class T>
ostream& operator<<(ostream& out, const CNode<T>& x)
   {x.Output(out); out << endl; return out;}

template<class T>
class HeadNode {
   friend LinkedMatrix<T>;
   friend ostream& operator<<
          (ostream&, const LinkedMatrix<T>&);
   friend istream& operator>>
          (istream&, LinkedMatrix<T>&);
   public:
      int operator !=(const HeadNode<T>& y)
         {return (row != y.row);}
      void Output(ostream& out) const
         {out << "row " << row;}
   private:
      int row;
      Chain<CNode<T> > a; // row chain
};

template<class T>
ostream& operator<<(ostream& out,
                    const HeadNode<T>& x)
   {x.Output(out); out << endl; return out;}

#endif
