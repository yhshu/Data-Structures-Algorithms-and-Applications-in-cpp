#ifndef Stack_
#define Stack_

// file nstack.h ... stack from scratch

template<class type>
class Stack
{
// LIFO objects
public:
   Stack(int MaxStackSize = 10); // constructor
   ~Stack() {delete [] stack;}
   int IsEmpty() {return top == -1;}
   int IsFull() {return top == MaxSize - 1;}
   int Top(type& x);
   int Add(const type& x);
   int Delete(type& x);
private:
   int top;
   int MaxSize;
   type *stack;
};

template<class type>
Stack<type>::Stack(int MaxStackSize)
{
MaxSize = MaxStackSize;
stack = new type[MaxSize];
top = -1;
}

template<class type>
int Stack<type>::Top(type& x)
{//set x to top element
if (IsEmpty()) return 0; //Top fails
x = stack[top];
return 1; //Top succeeds
}

template<class type>
int Stack<type>::Add(const type& x)
{//add x to stack
if (IsFull()) return 0; //add fails
stack[++top] = x;
return 1; //add succeeds
}

template<class type>
int Stack<type>::Delete(type& x)
{//delete top element and put it in x
if (IsEmpty()) return 0; //delete fails
x = stack[top--];
return 1; //delete succeeds
}

#endif
