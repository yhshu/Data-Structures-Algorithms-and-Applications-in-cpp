
#include<iostream.h>
#include<stdlib.h>
#include <time.h>
#include "hsort.h"
#include "minheap.h"
#include "eminheap.h"

struct  JobNode {
           int ID, time;
           operator int () const {return time;}
           };

struct  MachineNode {
           int ID, avail;
           operator int () const {return avail;}
           operator += (int x)
              {(*this).avail += x;
               return *this;}
           };

template <class type>
void LPT(type *a, int n, int m)
{// Construct an m machine LPT schedule
ExtendedMinHeap<MachineNode, int> H(m);
MachineNode x;
if (n <= m) {
   cout << "schedule one job per machine" << endl;
   return;}
HeapSort(a,n); //in ascending order
int i;
for (i = 1; i <= m; i++) //initialize machines
   {x.avail = 0; x.ID = i; H.Insert(x);}
//construct schedule
for (i = n; i >= 1; i--) {
   H.IncreaseMinKey(a[i].time, x);
//   cout << "Schedule job " << a[i].ID << " on machine "
//        << x.ID << " from " << x.avail << " to "
//        << x.avail + a[i].time << endl;
   }
}

void main(void)
{
JobNode a[10000];
//n is number of jobs, m is number of machines
//r is max job time
int n = 10000, r = 100, m = 100;
//initialize n jobs
for (int i=1; i<=n; i++) {a[i].time = 1 + rand() * r; a[i].ID = i;}
clock_t start, finish;
start = clock( );
int counter = 0; float seconds;
while (clock( ) - start < 10) {//at least 10 ticks
counter++;
LPT(a,n,m);
}
finish = clock( );
seconds = (finish - start) / CLK_TCK;
cout << n << ' ' << counter << ' ' << seconds
     << ' ' << seconds / counter << endl;
}
