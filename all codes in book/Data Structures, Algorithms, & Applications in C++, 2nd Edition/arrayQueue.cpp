// test array queue

#include <iostream>
#include "arrayQueue.h"
#include "myExceptions.h"

using namespace std;

int main(void)
{
   arrayQueue<int> q(4);

   // add a few elements
   q.push(1);
   cout << "Queue rear is " << q.back() << endl;
   q.push(2);
   cout << "Queue rear is " << q.back() << endl;
   q.push(3);
   cout << "Queue rear is " << q.back() << endl;
   q.push(4);
   cout << "Queue rear is " << q.back() << endl;

   cout << "Queue should be 1234, front to rear" << endl;

   // test empty and size
   if (q.empty())
      cout << "The queue is empty" << endl;
   else
      cout << "The queue is not empty" << endl;

   cout << "The queue size is " << q.size() << endl;

   while (!q.empty())
   {
      cout << "Queue front is " << q.front() << endl;
      q.pop();
      cout << "Popped front element" << endl;
   }

   try {q.pop();}
   catch (queueEmpty message)
   {
      cout << "Last pop failed " << endl;
      message.outputMessage();
   }

   // create a wraparound queue and do array doubling
   arrayQueue<int> r(4);
   r.push(1);
   r.push(2);
   r.push(3);
   r.pop();
   r.pop();
   r.push(4);
   r.push(5);
   r.push(6);
   r.push(7);

   cout << "Queue should be 34567, front to rear" << endl;

   // test empty and size
   if (r.empty())
      cout << "The queue is empty" << endl;
   else
      cout << "The queue is not empty" << endl;

   cout << "The queue size is " << r.size() << endl;

   while (!r.empty())
   {
      cout << "Queue front is " << r.front() << endl;
      r.pop();
      cout << "Popped front element" << endl;
   }

   return 0;
}
