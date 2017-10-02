
// formula-based stack
// extended to include Size
// and overloading of << and >>

#ifndef Stack_
#define Stack_

#include "xcept.h"


template<class T>
class Stack {
   friend ostream& operator<<
          (ostream&, const Stack<T>&);
   friend istream& operator>>
          (istream&, Stack<T>&);
   public:
      Stack(int MaxStackSize = 10);
      ~Stack() {delete [] stack;}
      bool IsEmpty() const {return top == -1;}
      bool IsFull() const {return top == MaxTop;}
      T Top() const;
      Stack<T>& Add(const T& x);
      Stack<T>& Delete(T& x);
      int Size() {return top + 1;}
   private:
      int top;    // current top of stack
      int MaxTop; // max value for top
      T *stack;   // element array
};

template<class T>
Stack<T>::Stack(int MaxStackSize)
{// Stack constructor.
   MaxTop = MaxStackSize - 1;
   stack = new T[MaxStackSize];
   top = -1;
}

template<class T>
T Stack<T>::Top() const
{// Return top element.
   if (IsEmpty()) throw OutOfBounds(); // Top fails
   else return stack[top];
}

template<class T>
Stack<T>& Stack<T>::Add(const T& x)
{// Add x to stack.
   if (IsFull()) throw NoMem(); // add fails
   stack[++top] = x;
   return *this;
}

template<class T>
Stack<T>& Stack<T>::Delete(T& x)
{// Delete top element and put it in x.
   if (IsEmpty()) throw OutOfBounds(); // delete fails
   x = stack[top--];
   return *this;
}

// overload >>
template<class T>
istream& operator>>(istream& in, Stack<T>& s)
{// Input stack s from top to bottom.
   // input and verify stack size
   int size;
   cout << "Enter size of stack" << endl;
   in >> size;
   if (size > s.MaxTop + 1) throw NoMem(); // fail

   s.top = size - 1;

   // input the stack elements and store in array
   cout << "Enter the elements from top to bottom"
        << endl;
   for (int i = s.top; i >= 0 ; i--)
      in >> s.stack[i];

   return in;
}

// overload <<
template <class T>
ostream& operator<<(ostream& out,
                    const Stack<T>& s)
{// Output the stack s from top to bottom

   // output stack size
   out << "The stack has " << (s.top + 1)
       << " element(s)" << endl;

   // output stack elements
   out << "The element(s) from top to bottom are"
       << endl;
   for (int i = s.top; i >= 0 ; i--)
      out << s.stack[i] << ' ';
   out << endl;

   return out;
}

#endif
