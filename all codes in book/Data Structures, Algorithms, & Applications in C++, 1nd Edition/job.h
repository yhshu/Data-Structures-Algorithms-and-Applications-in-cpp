// task and job classes for machine scheduling
#ifndef Job_
#define Job_

class Task {
   friend class Job;
   friend bool MoveToNextMachine(Job*);
   private:
      long time;
      int  machine;
};

class Job {
   friend bool MoveToNextMachine(Job*);
   friend Job* ChangeState(int);
   friend void Simulate();
   friend class Machine;
   public:
      Job(long id) {ID = id;
               Length = ArriveTime = 0;}
      void AddTask(int p, long t) {
              Task x;
              x.machine = p;
              x.time = t;
              TaskQ.Add(x);}
      long DeleteTask() {// delete next task
              Task x;
              TaskQ.Delete(x);
              Length += x.time;
              return x.time;}
   private:
      LinkedQueue<Task> TaskQ;
      long Length;      // sum of scheduled task times
      long ArriveTime;  // arrival time at current queue
      long ID;          // job identifier
};

#endif
