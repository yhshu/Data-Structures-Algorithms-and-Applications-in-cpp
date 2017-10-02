
// struct used in machine shop simulation
#ifndef machine_
#define machine_

#include "arrayQueue.h"
#include "job.h"

using namespace std;

struct machine
{
   arrayQueue<job*> jobQ;
                     // queue of waiting jobs for this machine
   int changeTime;   // machine change-over time
   int totalWait;    // total delay at this machine
   int numTasks;     // number of tasks processed on this machine
   job* activeJob;   // job currently active on this machine

   machine()
   {
      totalWait = 0;
      numTasks = 0;
      activeJob = NULL;
   }
};
#endif
