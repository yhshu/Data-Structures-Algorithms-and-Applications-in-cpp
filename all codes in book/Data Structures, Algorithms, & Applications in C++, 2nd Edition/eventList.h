// event list class used in machine scheduling

#ifndef eventList_
#define eventList_

#include "myExceptions.h"

using namespace std;

class eventList
{
   public:
      eventList(int theNumMachines, int theLargeTime)
      {// Initialize finish times for m machines.
         if (theNumMachines < 1)
            throw illegalParameterValue
                  ("number of machines must be >= 1");
         numMachines = theNumMachines;
         finishTime = new int [numMachines + 1];
   
         // all machines are idle, initialize with
         // large finish time
         for (int i = 1; i <= numMachines; i++)
            finishTime[i] = theLargeTime;
      }
      
      int nextEventMachine()
      {// Return machine for next event.
      
         // find first machine to finish, this is the
         // machine with smallest finish time
         int p = 1;
         int t = finishTime[1];
         for (int i = 2; i <= numMachines; i++)
            if (finishTime[i] < t)
            {// i finishes earlier
               p = i;
               t = finishTime[i];
            }
         return p;
      }
   
      int nextEventTime(int theMachine)
      {return finishTime[theMachine];}
   
      void setFinishTime(int theMachine, int theTime)
      {finishTime[theMachine] = theTime;}
   private:
      int* finishTime;   // finish time array
      int numMachines;   // number of machines
};
#endif
