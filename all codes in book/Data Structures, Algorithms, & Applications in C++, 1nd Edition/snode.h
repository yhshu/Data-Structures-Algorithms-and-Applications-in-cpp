#ifndef SimNode_
#define SimNode_

template <class T> class SimSpace;
template <class T> class SimChain;

template <class T>
class SimNode {
   friend SimSpace<T>;
   friend SimChain<T>;
   private:
      T data;
      int  link;
};

#endif
