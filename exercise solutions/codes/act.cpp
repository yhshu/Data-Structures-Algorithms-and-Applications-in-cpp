
#include<iostream.h>
#include "hsort.h"

class JobNode {
   friend void main(void);
   public:
      operator int () const
         {return time;}
   private:
     int ID,   // task ID
         time; // task time
};

template<class type>
void ACT(type *J, int n)
{// Reorder the n jobs so that the average
 // completion time is minimized
   HeapSort(J,n);
}

void main(void)
{
   int n = 12;  // number of tasks
   JobNode J[13];
   // create n jobs
   for (int i = 1; i <= n; i++) {
      J[i].ID = i;
      J[i].time = 20 - i;
      }
   ACT(J, n);
   cout << "The tasks should be done in the order" << endl;
   for (i = 1; i <= n; i++)
      cout << J[i].ID << ' ';
   cout << endl;
}
