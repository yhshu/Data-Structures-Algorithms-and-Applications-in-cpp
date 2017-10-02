// function to compute an expression using int value parameters

#include<iostream>

using namespace std;

int abc(int a, int b, int c)
{
   return a + b * c;
}

int main()
{
   cout << abc(2,3,4) << endl;
   return 0;
}

