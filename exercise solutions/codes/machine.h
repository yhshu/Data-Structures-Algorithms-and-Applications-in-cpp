


#ifndef Machine_
#define Machine_

class Machine {
   friend void main(void);
   public:
      operator int() const
      {return avail;}
   private:
      int avail;  // time machine gets free
      int ID;     // machine ID
};

#endif
