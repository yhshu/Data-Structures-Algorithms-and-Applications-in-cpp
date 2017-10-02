// test winner tree class

#include <iostream.h>
#include <stdlib.h>
#include "winner.h"
#include "winnode.h"

int winner(WinNode a[], int b, int c)
{// For a min winner tree.
   if (a[b].key <= a[c].key) return b;
   return c;
}

void main(void)
{
   WinnerTree<WinNode> W(20);
   WinNode element[20];
   int n;
   cout << "Enter number of players, between 8 and 20" << endl;
   cin >> n;
   if (n < 8 || n > 20)
      {cout << "Bad input" << endl;
       exit(1);}
   cout << "Enter player values" << endl;
   for (int i = 1; i <= n; i++)
      cin >> element[i].key;
   W.Initialize(element, n, winner);
   cout << "The winner tree is" << endl;
   W.Output();
   element[2].key = 0;
   W.RePlay(2, winner);
   cout << "Changed player 2 to zero, new tree is" << endl;
   W.Output();
   element[3].key = -1;
   W.RePlay(3, winner);
   cout << "Changed player 3 to -1, new tree is" << endl;
   W.Output();
   element[7].key = 2;
   W.RePlay(7, winner);
   cout << "Changed player 7 to 2, new tree is" << endl;
   W.Output();
}
