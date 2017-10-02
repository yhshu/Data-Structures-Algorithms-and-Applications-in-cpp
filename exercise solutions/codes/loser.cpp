
// test loser tree class

#include <iostream.h>
#include <stdlib.h>
#include "loser.h"
#include "losnode.h"

int winner(LoserNode a[], int b, int c)
{// For a min winner tree.
   if (a[b].key <= a[c].key) return b;
   return c;
}

void main(void)
{
   LoserTree<LoserNode> L(20);
   LoserNode element[20];
   int n;
   cout << "Enter number of players, between 8 and 20" << endl;
   cin >> n;
   if (n < 8 || n > 20)
      {cout << "Bad input" << endl;
       exit(1);}
   cout << "Enter player values" << endl;
   for (int i = 1; i <= n; i++)
      cin >> element[i].key;

   L.Initialize(element, n, winner);
   cout << "The loser tree is" << endl;
   L.Output();

   element[L.Winner()].key = 10;
   L.RePlay(winner);
   cout << "Changed previous winner to 10, new tree is" << endl;
   L.Output();

   element[L.Winner()].key = 12;
   L.RePlay(winner);
   cout << "Changed previous winner to 12, new tree is" << endl;
   L.Output();

   element[L.Winner()].key = 20;
   L.RePlay(winner);
   cout << "Changed previous winner to 20, new tree is" << endl;
   L.Output();
}
