// machine shop simulation

#include <iostream.h>
#include "lqueue.h"
#include "xcept.h"
#include "job.h"
#include "machine.h"
#include "eventl.h"

// globals
long Now = 0;           // current time
int m;                  // number of machines
long n;                 // number of jobs
long LargeTime = 10000; // finish before this time
EventList *EL;          // pointer to event list
Machine *M;             // array of machines

bool MoveToNextMachine(Job *J)
{// Move J to machine for next task.
 // Return false if no next machine for this job.
  if (J->TaskQ.IsEmpty()) {// no next task
     cout << "Job " << J->ID << " has completed at "
          << Now << " Total wait was "
          << (Now-J->Length) << endl;
     return false;}
  else {// job has a next task
        // get machine for next task
        int p = J->TaskQ.First().machine;
        // put on p's wait queue
        M[p].AddJob(J);
        J->ArriveTime = Now;
        // if p idle, schedule immediately
        if (EL->NextEvent(p) == LargeTime) {
           // machine is idle
           ChangeState(p);}
        return true;}
}

Job* ChangeState(int p)
{// Task on machine p has finished, schedule next one.
 // Return last job.
   Job* LastJob;
   if (!M[p].Active) {// in idle or change-over state
      LastJob = 0;
      // wait over, ready for new job
      if (M[p].JobQ.IsEmpty()) // no waiting job
            EL->SetFinishTime(p,LargeTime);
      else {// take job off Q and work on it
         M[p].JobQ.Delete(M[p].Active);
         M[p].TotalWait +=
              Now - M[p].Active->ArriveTime;
         M[p].NumTasks++;
         long t = M[p].Active->DeleteTask();
         EL->SetFinishTime(p, Now + t);}
      }
   else {// task has just finished on M[p]
         // schedule change-over time
         LastJob = M[p].Active;
         M[p].Active = 0;
         EL->SetFinishTime(p, Now + M[p].ChangeTime);}
   return LastJob;
}

void InputData()
{// Input machine shop data.
   cout << "Enter number of machines and jobs" << endl;
   cin >> m >> n;
   if (m < 1 || n < 1) throw BadInput();

   // create event and machine queues
   EL = new EventList(m,LargeTime);
   M = new Machine [m+1];
   
   // input the machine wait times
   cout << "Enter change-over times for machines"
        << endl;
   for (int j = 1; j <= m; j++) {
      long ct;  // change-over time
      cin >> ct;
      if (ct < 0) throw BadInput();
      M[j].SetChange(ct);
      }
   // input the n jobs
   Job *J;
   for (int i = 1; i <= n; i++) {
      cout << "Enter number of tasks for job " << i
           << endl;
      int tasks;  // number of tasks
      int first;  // machine for first task of job
      cin >> tasks;
      if (tasks < 1) throw BadInput();
      J = new Job(i);
      cout << "Enter the tasks (machine, time)"
           << " in process order" << endl;
      for (int j = 1; j <= tasks; j++) {// get tasks
         int p;    // machine number
         long tt;  // task time
         cin >> p >> tt;
         if (p < 1 || p > m || tt < 1) throw BadInput();
         if (j == 1) first = p; // job's first machine
         J->AddTask(p,tt);  // add task to task queue
         }
      M[first].AddJob(J);   // add job to machine for
      }                     // first task
}

void StartShop()
{// Load first jobs onto each machine.
   for (int p = 1; p <= m; p++)
      ChangeState(p);
}

void Simulate()
{// Process all n jobs to completion.
   int p;
   long t;
   while (n) {// at least one job left
      EL->NextEvent(p,t); // next machine to finish
      Now = t; // present time
      // change job on machine p
      Job *J = ChangeState(p);
      // move job J to its next machine
      // decrement n if J has finished
      if (J && !MoveToNextMachine(J)) n--;
      }
}

void OutputStats()
{// Output wait times at machine.
   cout << "Finish time = " << Now << endl;
   long TotalWait, NumTasks;
   for (int p = 1; p <= m; p++) {
      M[p].Stats(TotalWait, NumTasks);
      cout << "Machine " << p << " completed "
           << NumTasks << " tasks" << endl;
      cout << "The total wait time was " << TotalWait;
      cout << endl << endl;
      }
}

void main(void)
{// Machine shop simulation.
   try {
      InputData();    // get machine and job data
      StartShop();    // initial machine loading
      Simulate();     // run all jobs through shop
      OutputStats();} // output macine wait times
   catch (...) {
      cout << "An exception has occurred" << endl;}
}
