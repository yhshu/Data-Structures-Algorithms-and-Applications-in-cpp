
// header file equeue.h

#ifndef LinkedQueue_
#define LinkedQueue_

template <class type>
class Node {
public:
   type data;
   Node<type> *link;
};

template<class type>
class LinkedQueue
{// FIFO objects
public:
   LinkedQueue() {front = rear = 0;} // constructor
   ~LinkedQueue(); // destructor
   int IsEmpty()
      {return ((front) ? 0 : 1);}
   int IsFull();
   int First(type& x); // return first element of queue in x
   int Last(type& x); // return last element of queue in x
   int Add(const type& x); // add x to queue
   int Delete(type& x); // delete x from queue
   int Size();
   int Input();
   void Output();
   void Erase();
   void Split(LinkedQueue<type>& A, LinkedQueue<type>& B);
   void Combine(LinkedQueue<type>& A,
		LinkedQueue<type>& B);
protected:
   Node<type> *front, *rear;
};

template<class type>
LinkedQueue<type>::~LinkedQueue()
{
Node<type> *i;
while (front) {i = front->link; delete front; front = i;}
}

template<class type>
int LinkedQueue<type>::IsFull()
{
Node<type> *i;
i = new Node<type>;
if (i) {delete i; return 0;};
return 1;
}

template<class type>
int LinkedQueue<type>::First(type& x)
{//set x to first element
if (IsEmpty()) return 0; //First fails
x = front->data;
return 1;
}

template<class type>
int LinkedQueue<type>::Last(type& x)
{//set x to last element
if (IsEmpty()) return 0; //Last fails
x = rear->data;
return 1;
}

template<class type>
int LinkedQueue<type>::Add(const type& x)
{//add x to queue
Node<type> *i;
i = new Node<type>;
if (i) {
     i->data = x; i->link = 0;
     if (front) rear->link = i;
     else front = i;
     rear = i; return 1;
        };
return 0; // add fails 
}

template<class type>
int LinkedQueue<type>::Delete(type& x)
{//delete first element and put it in x
if (IsEmpty()) return 0; //delete fails
x = front->data;
Node<type> *i = front;
front = front->link;
delete i;
return 1;
}

template<class type>
int LinkedQueue<type>::Size()
{int i = 0;
Node<type> *x = front;
while (x) {x = x->link; i++;}
return i;
}


template<class type>
int LinkedQueue<type>::Input()
{
//empty out the queue
type x;
while (!IsEmpty()) Delete(x);
int length;
cout << "Enter size of queue" << endl;
cin >> length;
cout << "Enter the elements front-to-rear" << endl;
for (int i = 0; i < length ; i++) {
   cin >> x;
   if (!Add(x)) return 0;
   }
return 1;
}

template<class type>
void LinkedQueue<type>::Output()
{
cout << "The queue has " << Size() << " element(s)" << endl;
cout << "The element(s) front-to-rear are" << endl;
for (Node<type> *i = front; i ; i = i->link)
   cout << i->data << ' ';
cout << endl;
}

template<class type>
void LinkedQueue<type>::Erase()
{//destroy
Node<type> *i;
while (front)
   {i = front->link; delete front; front = i;}
}

template <class type>
void LinkedQueue<type>::Split(LinkedQueue<type>& A,
                             LinkedQueue<type>& B)
{// Split into A and B
A.Erase();
B.Erase();
while (front) {//not empty
   if (A.front) A.rear->link = front;
   else A.front = front;
   A.rear = front;
   front = front->link;
   if (front) {
      if (B.front) B.rear->link = front;
      else B.front = front;
      B.rear = front;
      front = front->link;}
   }
if (A.rear) A.rear->link = 0;
if (B.rear) B.rear->link = 0;
}

template <class type>
void LinkedQueue<type>::Combine(LinkedQueue<type>& A,
				LinkedQueue<type>& B)
{// Combine the two queues A and B
Erase();
//special cases ... A or B empty
if (!A.front) {front = B.front; rear = B.rear;
               B.front = 0; return;}
if (!B.front) {front = A.front; rear = A.rear;
               A.front = 0; return;}
//copy first nodes
front = A.front; A.front = A.front->link;
front->link = rear = B.front; B.front = B.front->link; 
//get rest
while (A.front && B.front) {
   rear->link = A.front; A.front = A.front->link;
   rear = rear->link;
   rear->link = B.front; B.front = B.front->link;
   rear = rear->link;}
if (A.front) {rear->link = A.front; rear = A.rear;
              A.front = 0;}
else {rear->link = B.front; rear = B.rear;
      B.front = 0;}
}

#endif
