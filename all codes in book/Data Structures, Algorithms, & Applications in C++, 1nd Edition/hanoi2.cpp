
// Towers of Hanoi with state saving in stacks

#include <iostream.h>
#include "stack.h"


class Hanoi {
   friend void TowersOfHanoi(int);
   public:
      void TowersOfHanoi(int n, int x, int y, int z);
   private:
      Stack<int> *S[4]; // array of pointers to stacks
};

void Hanoi::TowersOfHanoi(int n, int x, int y, int z)
{// Move the top n disks from tower x to tower y.
 // Use tower z for intermediate storage.
   int d;  // disk number
   if (n > 0) {
      TowersOfHanoi(n-1, x, z, y);
      S[x]->Delete(d);  // remove a disk from x
      S[y]->Add(d);  // put this disk on tower y
   // ShowState();
   // substitute ShowState code for test run
      cout << "Move disk " << d << " from tower "
           << x << " to tower " << y << endl;
      TowersOfHanoi(n-1, z, y, x);}
}

void TowersOfHanoi(int n)
{// Preprocessor for Hanoi::towersOfHanoi.
   Hanoi X;
   // create three stacks of size n each
   X.S[1] = new Stack<int> (n);
   X.S[2] = new Stack<int> (n);
   X.S[3] = new Stack<int> (n);
   
   for (int d = n; d > 0; d--) // initialize
      X.S[1]->Add(d); // add disk d to tower 1
   
   // move n disks from tower 1 to 3 using 2 as
   // intermediate tower
   X.TowersOfHanoi(n, 1, 2, 3);
}

void main(void)
{
   cout << "Moves for a three disk problem are" << endl;
   TowersOfHanoi(3);
}
