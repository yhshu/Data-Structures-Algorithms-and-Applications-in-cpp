// abstract class winner tree
// all methods are pure virtual functions

#ifndef winnerTree_
#define winnerTree_

using namespace std;

template<class T>
class winnerTree 
{
   public:
      virtual ~winnerTree() {}
      virtual void initialize(T *thePlayer, int theNumberOfPlayers) = 0;
         // create winner tree with thePlayer[1:numberOfPlayers]
      virtual int winner() const = 0;
         // return index of winner
      virtual void rePlay(int thePLayer) = 0;
         // replay matches following a change in thePLayer
};
#endif

