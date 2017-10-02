
#ifndef Object_
#define Object_

class Object {
   friend float Knapsack(int [], int [], int, int, float []);
   friend float Knapsack(int [], int [], int, int, int []);
   public:
      operator float() const
      {return d;}
   private:
      int ID;  // object identifier
      float d; // profit density
};

#endif
