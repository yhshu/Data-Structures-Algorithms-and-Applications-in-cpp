#include<iostream.h>

int Abc(int a, int b, int c)
{
   return a+b+b*c+(a+b-c)/(a+b)+4;
}

void main(void)
{
   cout << Abc(2,3,4) << endl;
}

