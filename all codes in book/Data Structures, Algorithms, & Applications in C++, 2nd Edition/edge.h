// abstract class for graph edges

#ifndef edge_
#define edge_

using namespace std;

template <class T>
class edge
{
   public:
      virtual ~edge() {};
      virtual int vertex1() const = 0;
      virtual int vertex2() const = 0;
      virtual T weight() const = 0;
};
      
#endif
