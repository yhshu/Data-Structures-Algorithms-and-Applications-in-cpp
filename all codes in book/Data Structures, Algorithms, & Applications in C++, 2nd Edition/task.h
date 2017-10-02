// task struct used in machine shop simulation
#ifndef task_
#define task_

using namespace std;

struct task
{
   int machine;
   int time;

   task(int theMachine = 0, int theTime = 0)
   {
      machine = theMachine;
      time = theTime;
   }
};

#endif
