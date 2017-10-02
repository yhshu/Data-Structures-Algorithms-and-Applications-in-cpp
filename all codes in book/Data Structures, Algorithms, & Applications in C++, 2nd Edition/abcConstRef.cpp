// template function with const reference parameters 
// to compute an expression

#include<iostream>

using namespace std;

template<class T>
T abc(const T& a, const T& b, const T& c)
{
   return a + b * c;
}

int main()
{
   cout << abc(2,3,4) << endl;
   return 0;
}

