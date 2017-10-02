
// abstract class for graph vertex iterator

#ifndef vertexIterator_
#define vertexIterator_


using namespace std;

template<class T>
class vertexIterator 
{
   public:
      virtual ~vertexIterator() {}
      virtual int next() = 0;
      virtual int next(T&) = 0;
};
#endif
