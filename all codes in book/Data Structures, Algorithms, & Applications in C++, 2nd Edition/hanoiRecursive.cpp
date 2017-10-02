// Recursive Towers of Hanoi

#include <iostream>

using namespace std;

void towersOfHanoi(int n, int x, int y, int z)
{// Move the top n disks from tower x to tower y.
 // Use tower z for intermediate storage.
   if (n > 0)
   {
      towersOfHanoi(n-1, x, z, y);
      cout << "Move top disk from tower " << x 
           << " to top of tower " << y << endl;
      towersOfHanoi(n-1, z, y, x);
   }
}

void main(void)
{
   cout << "Moves for a three disk problem are" << endl;
   towersOfHanoi(3,1,2,3);
}
