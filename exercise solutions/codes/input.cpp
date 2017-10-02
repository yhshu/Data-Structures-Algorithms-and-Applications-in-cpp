
#include <iostream.h>


template<class T>
bool Input(T& x)
{// Input a nonnegative value.
   int NumOfAttempts = 3;

   // try at most NumOfAttempts times
   for (int i = 0; i < NumOfAttempts; i++) {
      cout << "Enter a nonnegative value" << endl;
      cin >> x;
      if (x >= 0) return true;
      cout << x << " is not nonnegative" << endl;
      }
   // did not get nonnegative value
   cout << "Sorry, you get only "
        << NumOfAttempts << " chances."
        << endl;
   return false;
}


void main()
{// Test Input.

int a;
if (Input(a)) cout << "The number is " << a << endl;
else cout << "Did not get a nonnegative number" << endl;
}
