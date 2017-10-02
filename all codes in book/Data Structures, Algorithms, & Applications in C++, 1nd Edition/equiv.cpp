// offline equivalence classes

#include <iostream.h>
#include <stdlib.h>
#include "chain.h"
#include "citer.h"
#include "lstack.h"

void main(void)
{// Offline equivalenece classes.
   int n, r;

   // input n and r
   cout << "Enter number of elements" << endl;
   cin >> n;
   if (n < 2) {cerr << "Too few elements" << endl;
               exit(1);}
   cout << "Enter number of relations" << endl;
   cin >> r;
   if (r < 1) {cerr << "Too few relations" << endl;
               exit(1);}

   // create an array of n chains
   Chain<int> *chain;
   try {chain = new Chain<int> [n+1];}
   catch (NoMem) {cerr << "Out of memory" << endl;
                  exit(1);}
              
   // input the r relations and put on chains
   for (int i = 1; i <= r; i++) {
      cout << "Enter next relation/pair" << endl;
      int a, b;
      cin >> a >> b;
      chain[a].Insert(0,b);
      chain[b].Insert(0,a);
      }
   
   // initialize to output classes
   LinkedStack<int> stack;
   bool *out;
   try {out = new bool [n+1];}
   catch (NoMem) {cerr << "Out of memory" << endl;
                  exit(1);}
   for (i = 1; i <= n; i++)
      out[i] = false;
   
   // output classes
   for (i = 1; i <= n; i++)
     if (!out[i]) {// start of a new class
        cout << "Next class is: " << i << ' ';
        out[i] = true;
        stack.Add(i);
        // get rest of class from stack
        while (!stack.IsEmpty()) {
           int *q, j;
           stack.Delete(j);

           // elements on chain[j] are in
           // same class, use iterator c
           // to get them
           ChainIterator<int> c;
           q = c.Initialize(chain[j]);
           while (q) {// q is in same class
              if (!out[*q]) {
                    cout << *q << ' ';
                    out[*q] = true;
                    stack.Add(*q);}
              q = c.Next();
              }
           }
        cout << endl;
        }

   cout << endl << "End of class list" << endl;
}  
