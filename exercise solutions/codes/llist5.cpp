
// split a list into two

#include<iostream.h>
#include "llist5.h"
void main(void)
{
   int n = 15;
   LinearList<int> X(20), Y(20), Z(20);
   
   // initialize list to be split
   for (int i = 0; i < n; i++)
      X.Insert(0,i);
   cout << "The list is" << endl;
   cout << X << endl;
   
   X.Split(Y,Z);
   
   cout << "The first split list is" << endl;
   cout << Y << endl;
   
   cout << "The second split list is" << endl;
   cout << Z << endl;
}
