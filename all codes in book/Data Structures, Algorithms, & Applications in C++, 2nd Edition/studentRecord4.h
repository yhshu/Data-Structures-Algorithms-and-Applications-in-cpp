

#ifndef studentRecord_
#define studentRecord_

using namespace std;

struct studentRecord 
{
   int exam1, exam2, exam3;
   int name;

   operator int() const {return exam1;}
};

ostream& operator<<(ostream& out, const studentRecord& x)
{
   out << x.name << ' ' << x.exam1 << ' ' << x.exam2 
       << ' ' << x.exam3 << endl;
   return out;
}

#endif
