// general template function with reference parameters
// to compute an expression

#include<iostream>

using namespace std;

template<class Ta, class Tb, class Tc>
Ta abc(const Ta& a, const Tb& b, const Tc& c)
{
   return a + b * c;
}

int main()
{
   cout << abc(2,3,4) << endl;
   return 0;
}

