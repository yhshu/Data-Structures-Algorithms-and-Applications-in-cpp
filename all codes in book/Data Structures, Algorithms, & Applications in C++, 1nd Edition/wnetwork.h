// file wnetwork.h
// functions for weighted networks

#ifndef WNetwork_
#define WNetwork_

#include "network.h"

template <class T>
class WNetwork : virtual public Network
{
   public:
      virtual void First(int i, int& j, T& c) = 0;
      virtual void Next(int i, int& j, T& c) = 0;
};

#endif;
