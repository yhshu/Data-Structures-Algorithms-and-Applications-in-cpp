//Machine class used in machine shop simulation
#ifndef Machine_
#define Machine_

class Machine {
   friend Job* ChangeState(int);
   public:
      Machine() {TotalWait = NumTasks = 0;
                 Active = 0;}
      bool IsEmpty() {return JobQ.IsEmpty();}
      void AddJob(Job* x) {JobQ.Add(x);}
      void SetChange(long w) {ChangeTime = w;}
      void Stats(long& tw, long& nt)
              {tw = TotalWait;
               nt = NumTasks;}
   private:
      LinkedQueue<Job*> JobQ; // queue of waiting jobs
      long ChangeTime;  // machine changeover time
      long TotalWait;   // total delay at this machine
      long  NumTasks;   // number of tasks processed
      Job *Active;      // pointer to current job
};

#endif
