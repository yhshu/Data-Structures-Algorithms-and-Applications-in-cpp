#ifndef LPTNodes_
#define LPTNodes_


class  JobNode {
   friend void LPT(JobNode *, int, int);
   friend void main(void);
   public:
      operator int () const {return time;}
   private:
      int ID,    // job identifier
          time;  // processing time
};

class  MachineNode {
   friend void LPT(JobNode *, int, int);
   public:
      operator int () const {return avail;}
      operator += (int x)
         {(*this).avail += x;
          return *this;}
   private:
      int ID,     // machine identifier
          avail;  // when it becomes free
};

#endif
