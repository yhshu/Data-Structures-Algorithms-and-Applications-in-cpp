

// average completion time with m persons

#include <iostream.h>
#include "hsort.h"

class Task {
   friend void main(void);
   friend void ACT(Task J[], int n, int m);
   public:
      operator int () const
         {return time;}
   private:
     int ID,      // task ID
         time,    // task time
         person;  // person who is to do the task
};

template <class T>
void ACT(T J[], int n, int m)
{// Reorder the n tasks so that the average
 // completion time is minimized.
 // Tasks are assigned to m persons.
   HeapSort(J,n);
   // assign tasks to persons in round-robin fashion
   for (int i = 1; i <= n; i++)
      J[i].person = (i-1) % m + 1;
}

void main(void)
{
   int n = 12;  // number of tasks
   int m = 5;   // number of persons
   Task J[13];
   // create n tasks
   for (int i = 1; i <= n; i++) {
      J[i].ID = i;
      J[i].time = 20 - i;
      }
   ACT(J, n, m);
   cout << "The tasks should be done in the order given below" << endl;
   for (i = 1; i <= n; i++)
      cout << J[i].ID << " by person " << J[i].person << endl;
}
