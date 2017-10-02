   
// output LPT schedules

#include <iostream>
#include "minHeap.h"
#include "heapSort.h"
#include "lptNodes.h"

using namespace std;

void makeSchedule(jobNode a[], int n, int m)
{// Output an m machine LPT schedule for the jobs a[1:n].
   if (n <= m)
   {
      cout << "Schedule each job on a different machine." << endl;
      return;
   }

   heapSort(a, n); // in ascending order

   // initialize m machines and the min heap
   minHeap<machineNode> machineHeap(m);
   for (int i = 1; i <= m; i++)
      machineHeap.push(machineNode(i, 0));

   // construct schedule
   for (int i = n; i >= 1; i--)
   {// schedule job i on first free machine
      machineNode x =  machineHeap.top();
      machineHeap.pop();
      cout << "Schedule job " << a[i].id 
           << " on machine " << x.id << " from " << x.avail
           << " to " << (x.avail + a[i].time) << endl;
      x.avail += a[i].time;  // new available time for this machine
      machineHeap.push(x);
   }
}

void main(void)
{
   jobNode a[11];
   int n = 10;
   for (int i = 1; i <= n; i++)
   {
      a[i].id = i;
      a[i].time = 2 * i * i;
   }
   makeSchedule(a, 10, 3);
}
