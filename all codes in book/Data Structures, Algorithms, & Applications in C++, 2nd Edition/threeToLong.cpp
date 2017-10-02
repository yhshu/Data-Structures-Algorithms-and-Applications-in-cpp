
// convert characters 0, 1 and 2 of a string into a long

#include <iostream>
#include <string>

using namespace std;


long threeToLong(string s)
{// Assume s.length() >= 3.
   // leftmost char
   long answer = s.at(0);

   // shift left 8 bits and add in next char
   answer = (answer << 8) + s.at(1);

   // shift left 8 bits and add in next char
   return (answer << 8) + s.at(2);
}

// test program 
void main(void)
{
    string s = "abc";
    for (int i = 0; i < 3; i++)
       cout << s.at(i) << " " << ((int) s.at(i)) << endl;

    cout << threeToLong(s) << endl;
}
