// dynamic programming recursive knapsack

#include <iostream.h>
#include <stdlib.h>
#include "dosmax.h"  // has max() and min()

int p[6] = {0, 6, 3, 5, 4, 6};
int w[6] = {0, 2, 2, 6, 5, 4};
int x[6];
int n = 5;
int c = 10;

int F(int i, int y)
{// Return f(i,y).
   if (i == n) return (y < w[n]) ? 0 : p[n];
   if (y < w[i]) return F(i+1,y); 
   return max(F(i+1,y), F(i+1,y-w[i]) + p[i]);
}

void main(void)
{
   cout << "Optimal value is ";
   cout << F(1,c) << endl;
}
