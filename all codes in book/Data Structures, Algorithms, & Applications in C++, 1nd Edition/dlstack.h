// header file lstack.h
#ifndef LinkedStack_
#define LinkedStack_

#include "chain.h"
#include "xcept.h"

template<class T>
class LinkedStack : private Chain<T> {
public:   
   bool IsEmpty() const   
      {return Chain<T>::IsEmpty();}   
   bool IsFull() const;   
   T Top() const   
      {if (IsEmpty()) throw OutOfBounds();   
       T x; Find(1, x); return x;}   
   LinkedStack<T>& Add(const T& x)   
      {Insert(0, x); return *this;}   
   LinkedStack<T>& Delete(T& x)   
       {Chain<T>::Delete(1, x); return *this;}   
};

template<class T>
bool LinkedStack<T>::IsFull() const
{//Is stack full?
   try {ChainNode<T> *p = new ChainNode<T>;
        delete p; return false;}
   catch (NoMem) {return true;}
}

#endif;
