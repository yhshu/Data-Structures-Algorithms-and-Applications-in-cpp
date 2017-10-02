
#ifndef studentRecord_
#define studentRecord_

#include <string>

using namespace std;

struct studentRecord 
{
   int score;
   string* name;

   operator int() const {return score;}
      // type conversion from studentRecord to int
};

ostream& operator<<(ostream& out, const studentRecord& x)
   {out << x.score << ' ' << *x.name << endl; return out;}

#endif
