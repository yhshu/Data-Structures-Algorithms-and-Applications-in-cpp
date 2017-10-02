#ifndef studentRecord_
#define studentRecord_

#include <string>

using namespace std;
struct studentRecord 
{
   int score;
   string* name;

   int operator !=(studentRecord x) const
      {return (score != x.score);}
};

ostream& operator<<(ostream& out, const studentRecord& x)
   {out << x.score << ' ' << *x.name << endl; return out;}

#endif
