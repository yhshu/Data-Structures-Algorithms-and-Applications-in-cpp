#ifndef LPTNodes_
#define LPTNodes_


class jobNode
{
   friend void makeSchedule(jobNode *, int, int);
   friend void main(void);
   public:
      operator int () const {return time;}
   private:
      int id,    // job identifier
          time;  // processing time
};

class machineNode
{
   friend void makeSchedule(jobNode *, int, int);
   public:
      machineNode(int theID = 0, int theAvail = 0)
         {id = theID; avail = theAvail;}
      operator int () const {return avail;}
   private:
      int id,     // machine identifier
          avail;  // when it becomes free
};

#endif
