
// file abslist.h
#ifndef AbstractList_
#define AbstractList_

template<class T>
class AbstractList {
   public:
      virtual bool IsEmpty() const = 0;
      virtual int Length() const = 0;
      virtual bool Find(int k, T& x) const = 0;
         //return the k'th element of list in variable x
      virtual int Search(const T& x) const = 0;
         //return position of x
      virtual AbstractList<T>& Delete(int k, T& x) = 0;
         //delete k'th element of list and return in x
      virtual AbstractList<T>&
                      Insert(int k, const T& x) = 0;
         //insert x just after k'th element
      virtual void Output(ostream& out) const = 0;
};

#endif
