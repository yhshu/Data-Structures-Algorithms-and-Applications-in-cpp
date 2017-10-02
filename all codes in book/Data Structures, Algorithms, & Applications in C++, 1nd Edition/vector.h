
#ifndef Vector_
#define Vector_

#include <iostream.h>
#include "xcept.h"

template<class T>
class Vector {
public:
   Vector(int size = 0);
   Vector(const Vector<T>& v); //copy constructor
   ~Vector() {delete [] element;}
   T& operator[](int x) const;
   int Size() {return size;}
   Vector<T>& operator=(const Vector<T>& v);
   Vector<T> operator+() const; //unary +
   Vector<T> operator+(const Vector<T>& v) const;
   Vector<T> operator-() const; //unary minus
   Vector<T> operator-(const Vector<T>& v) const;
   Vector<T> operator*(const Vector<T>& v) const;
   Vector<T>& operator+=(const T& x);
   void Output(ostream& out) const;
private:
    int size;
    T *element; //array
};  

template<class T>
Vector<T>::Vector(int sz)
{//create
if (sz < 0) throw BadInitializers();
size = sz;
element = new T[sz];
}

template<class T>
Vector<T>::Vector(const Vector<T>& v)
{//copy constructor
size = v.size;
element = new T[size];
for (int i = 0; i < size; i++)
   element[i] = v.element[i];
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v)
{//overload assignment operator
if (this != &v) {//not self assignment
   delete [] element;
   size = v.size;
   element = new T[size];
   for (int i = 0; i < size; i++)
      element[i] = v.element[i];
   }
return *this;
}

template<class T>
T& Vector<T>::operator[](int x) const
{//return reference to element x
if (x < 1 || x > size) throw OutOfBounds();
return element[x - 1];
}

template<class T>
Vector<T> Vector<T>::operator+(const Vector<T>& v) const
{
if (size != v.size) throw SizeMismatch();
Vector<T> w(size);
for (int i = 0; i < size; i++)
    w.element[i] = element[i] + v.element[i];
return w;
}

template<class T>
Vector<T> Vector<T>::operator-(const Vector<T>& v) const
{
if (size != v.size) throw SizeMismatch();
Vector<T> w(size);
for (int i = 0; i < size; i++)
    w.element[i] = element[i] - v.element[i];
return w;
}

template<class T>
Vector<T> Vector<T>::operator-() const
{//unary minus
Vector<T> w(size);
for (int i = 0; i < size; i++)
    w.element[i] = -element[i];
return w;
}

template<class T>
Vector<T> Vector<T>::operator*(const Vector<T>& v) const
{
if (size != v.size) throw SizeMismatch();
Vector<T> w(size);
for (int i = 0; i < size; i++)
    w.element[i] = element[i] * v.element[i];
return w;
}

template<class T>
Vector<T>& Vector<T>::operator+=(const T& x)
{
for (int i = 0; i < size; i++)
    element[i] += x;
return *this;
}

template<class T>
void Vector<T>::Output(ostream& out) const
{// put the vector into the stream out
for (int i = 0; i < size; i++)
   out << element[i] << "  ";
}

//overload <<
template <class T>
ostream& operator<<(ostream& out, const Vector<T>& x)
{x.Output(out); return out;}

#endif
