

#ifndef Task_
#define Task_

class Task {
   friend void main(void);
   public:
      operator int() const
      {return start;}
   private:
      int start;  // task start time
      int finish; // task finish time
      int ID;     // task ID
};

#endif
