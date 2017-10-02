

#include <iostream.h>
#include "minheap.h"
#include "task2.h"

void main(void)
{// Output a maximum selection of tasks that can be done
 // on a single machine.

   // input the number of tasks
   int n;  // number of tasks
   cout << "Enter the number of tasks" << endl;
   cin >> n;
   if (n < 1) {cout << "Must be more than 0" << endl;
               exit(1);}

   // input and store the n tasks in a task array
   Task *t = new Task [n+1];
   for (int i = 1; i <= n; i++) {
      cout << "Enter the start and finish time of task "
           << i << endl;
      cin >> t[i].start >> t[i].finish;
      if (t[i].start < 0 || t[i].finish <= 0
          || t[i].start >= t[i].finish) {
          cout << "Bad start and/or finish time"
               << endl;
          exit(1);
          }
      t[i].ID = i;
      }

      // initialize a min heap with n tasks
      MinHeap<Task> H(1);
      H.Initialize(t,n,n);

      // select tasks
      cout << "The selected tasks are ";
      int avail = 0;  // time machine gets free
      for (i = 1; i <= n; i++) {
         // get task with least finish time
         Task w;
         H.DeleteMin(w);
         if (w.start >= avail) {
             // select the task
             cout << w.ID << " ";
             avail = w.finish;
             }
         }  
}
