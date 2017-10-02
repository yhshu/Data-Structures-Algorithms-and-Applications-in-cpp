#ifndef Object_
#define Object_

class Object {
   friend int Knapsack(int *, int *, int, int, int *);
   public:
      int operator<=(Object a) const
      {return (d >= a.d);}
   private:
      int ID;
      float d; // profit density
};

#endif
