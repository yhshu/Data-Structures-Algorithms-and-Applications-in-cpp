// job class used in machine scheduling

#ifndef job_
#define job_

#include "task.h"
#include "arrayQueue.h"

using namespace std;

struct job
{
   arrayQueue<task> taskQ;   // this job's tasks
   int length;               // sum of scheduled task times
   int arrivalTime;          // arrival time at current queue
   int id;                   // job identifier

   job(int theId = 0)
   {
      id = theId;
      length = 0;
      arrivalTime = 0;
   }

   void addTask(int theMachine, int theTime)
   {
      task theTask(theMachine, theTime);
      taskQ.push(theTask);
   }

   int removeNextTask()
   {// Remove next task of job and return its time.
    // Also update length.
   
      int theTime =  taskQ.front().time;
      taskQ.pop();
      length += theTime;
      return theTime;
   }
};
#endif
