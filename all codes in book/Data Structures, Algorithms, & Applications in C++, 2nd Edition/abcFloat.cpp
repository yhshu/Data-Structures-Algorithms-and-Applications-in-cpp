// function to compute an expression using float value parameters

#include<iostream>

using namespace std;

float abc(float a, float b, float c)
{
   return a + b * c;
}

int main()
{
   cout << abc(2,3,4) << endl;
   return 0;
}

