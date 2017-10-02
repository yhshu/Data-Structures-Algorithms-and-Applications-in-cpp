// machine shop simulation

#include <iostream>
#include "task.h"
#include "job.h"
#include "machine.h"
#include "eventList.h"
#include "myExceptions.h"

using namespace std;

// global variables
int timeNow;             // current time
int numMachines;         // number of machines
int numJobs;             // number of jobs
eventList* eList;        // pointer to event list
machine* mArray;         // array of machines
int largeTime = 10000;   // all machines finish before this

// functions
job* changeState(int);

bool moveToNextMachine(job* theJob)
{// Move theJob to machine for its next task.
 // Return false iff no next task.

   if (theJob->taskQ.empty())
   {// no next task
      cout << "Job " << theJob->id << " has completed at "
           << timeNow << " Total wait was " 
           << (timeNow - theJob->length) << endl;
      return false;
   }
   else
   {// theJob has a next task
    // get machine for next task
      int p = theJob->taskQ.front().machine;
      // put on machine p's wait queue
      mArray[p].jobQ.push(theJob);
      theJob->arrivalTime = timeNow;
      // if p idle, schedule immediately
      if (eList->nextEventTime(p) == largeTime)
         // machine is idle
         changeState(p);
      
      return true;
   }
}

job* changeState(int theMachine)
{// Task on theMachine has finished, schedule next one.
 // Return last job run on this machine.
   job* lastJob;
   if (mArray[theMachine].activeJob == NULL) 
   {// in idle or change-over state
      lastJob = NULL;
      // wait over, ready for new job
      if (mArray[theMachine].jobQ.empty()) // no waiting job
            eList->setFinishTime(theMachine, largeTime);
      else
      {// take job off the queue and work on it
         mArray[theMachine].activeJob = 
               mArray[theMachine].jobQ.front();
         mArray[theMachine].jobQ.pop();
         mArray[theMachine].totalWait +=
              timeNow - mArray[theMachine].activeJob->arrivalTime;
         mArray[theMachine].numTasks++;
         int t = mArray[theMachine].activeJob->removeNextTask();
         eList->setFinishTime(theMachine, timeNow + t);
      }
   }
   else
   {// task has just finished on theMachine
    // schedule change-over time
      lastJob = mArray[theMachine].activeJob;
      mArray[theMachine].activeJob = NULL;
      eList->setFinishTime(theMachine, timeNow +
                           mArray[theMachine].changeTime);
   }

   return lastJob;
}

void inputData()
{// Input machine shop data.

   cout << "Enter number of machines and jobs" << endl;
   cin >> numMachines >> numJobs;
   if (numMachines < 1 || numJobs < 1)
         throw illegalInputData
               ("number of machines and jobs must be >= 1");

   // create event and machine queues
   eList = new eventList(numMachines, largeTime);
   mArray = new machine [numMachines + 1];
   
   // input the change-over times
   cout << "Enter change-over times for machines" << endl;
   int ct;
   for (int j = 1; j <= numMachines; j++)
   {
      cin >> ct;
      if (ct < 0)
         throw illegalInputData("change-over time must be >= 0");
      mArray[j].changeTime = ct;
   }

   // input the jobs
   job* theJob;
   int numTasks, firstMachine, theMachine, theTaskTime;
   for (int i = 1; i <= numJobs; i++)
   {
      cout << "Enter number of tasks for job " << i << endl;
      cin >> numTasks;
      firstMachine = 0;   // machine for first task
      if (numTasks < 1)
         throw illegalInputData("each job must have > 1 task");

      // create the job
      theJob = new job(i);
      cout << "Enter the tasks (machine, time)"
           << " in process order" << endl;
      for (int j = 1; j <= numTasks; j++)
      {// get tasks for job i
         cin >> theMachine >> theTaskTime;
         if (theMachine < 1 || theMachine > numMachines
             || theTaskTime < 1)
         throw illegalInputData("bad machine number or task time");
         if (j == 1)
            firstMachine = theMachine;    // job's first machine
         theJob->addTask(theMachine, theTaskTime);  // add to
      }                                             // task queue
      mArray[firstMachine].jobQ.push(theJob);
   }                                           
}

void startShop()
{// Load first jobs onto each machine.
   for (int p = 1; p <= numMachines; p++)
      changeState(p);
}

void simulate()
{// Process all jobs to completion.
   while (numJobs > 0)
   {// at least one job left
      int nextToFinish = eList->nextEventMachine();
      timeNow = eList->nextEventTime(nextToFinish);
      // change job on machine nextToFinish
      job* theJob = changeState(nextToFinish);
      // move theJob to its next machine
      // decrement numJobs if theJob has finished
      if (theJob != NULL && !moveToNextMachine(theJob))
         numJobs--;
   }
}

void outputStatistics()
{// Output wait times at machines.
   cout << "Finish time = " << timeNow << endl;
   for (int p = 1; p <= numMachines; p++)
   {
      cout << "Machine " << p << " completed "
           << mArray[p].numTasks << " tasks" << endl;
      cout << "The total wait time was "
           << mArray[p].totalWait << endl;
      cout <<  endl;
   }
}

void main()
{
   inputData();         // get machine and job data
   startShop();         // initial machine loading
   simulate();          // run all jobs through shop
   outputStatistics();  // output machine wait times
}
