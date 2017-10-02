// event queue for machine shop simulation
#ifndef EventList_
#define EventList_

class EventList {
   public:
      EventList(int m, long BigT);
      ~EventList(){delete [] FinishTime;}
   	void NextEvent(int& p, long& t);
      long NextEvent(int p) {return FinishTime[p];}
      void SetFinishTime(int p, long t)
              {FinishTime[p] = t;}
   private:
      long *FinishTime; // finish time array
      int NumMachines;  // number of machines in shop
};

EventList::EventList(int m, long BigT)
{// Initialize finish times for m machines.
   if (m < 1) throw BadInitializers();
   FinishTime = new long [m+1];
   NumMachines = m;
   // all machines idle, initialize with
   // large finish time
   for (int i = 1; i <= m; i++)
      FinishTime[i] = BigT;
}

void EventList::NextEvent(int& p, long& t)
{// Return machine and time for next event.
   // find first machine to finish, this is
   // machine with smallest finish time
   p = 1;
   t = FinishTime[1];
   for (int i = 2; i <= NumMachines; i++)
      if (FinishTime[i] < t) {// i finishes earlier
         p = i;
         t = FinishTime[i];}
}

#endif
