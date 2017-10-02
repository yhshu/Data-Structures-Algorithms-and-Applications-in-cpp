
// offline equivalence classes
// from basics; chain and linked stack not used

#include <iostream.h>
#include "xcept.h"
#include <stdlib.h>

class Node {
   friend void main(void);
   private:
      int element;
      Node *link;  // pointer to Node
};

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

   // create an array of n of pointers
   // to first nodes in chains
   Node **first;  // 1D array of pointers to Node
   try {first = new Node* [n+1];}
   catch (NoMem) {cerr << "Out of memory" << endl;
                  exit(1);}

   // initialize chains to empty
   for (int i = 1; i <= n; i++)
      first[i] = 0;
              
   // input the r relations and put on chains
   for (i = 1; i <= r; i++) {
      cout << "Enter next relation/pair" << endl;
      int a, b;
      cin >> a >> b;
      Node *x;
      // get a node for chain a 
      x = new Node;
      x->element = b;

      // insert at front of chain a 
      x->link = first[a];
      first[a] = x;

      // get a node for chain b
      x = new Node;
      x->element = a;

      // insert at front of chain b
      x->link = first[b];
      first[b] = x;
      }
   
   // initialize to output classes
   Node *top = 0;   // pointer to top of stack
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

        int j = i;
        do {
           // elements on chain j  are in
           // same class; process the chain
           Node *q = first[j];
           while (q) // q->element is in same class
              if (!out[q->element]) {
                    cout << q->element << ' ';
                    out[q->element] = true;

                    // save pointer to next node
                    Node *next = q->link;
                    
                    // add q->element to stack
                    q->link = top;
                    top = q;

                    // set q to next node on chain
                    q = next;}
              else q = q->link;
           if (!top) break;
           // set to process a chain from the stack
           j = top->element;
           top = top->link;
           } while (true);
        cout << endl;
        }

   cout << endl << "End of class list" << endl;
}  
