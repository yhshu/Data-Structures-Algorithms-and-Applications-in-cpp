
// simulated chain iterator

#ifndef SimChainIterator_
#define SimChainIterator_

template<class T>
class SimChainIterator {
   public:
      T* Initialize(const SimChain<T>& c)
            {location = c.first;
             S = &c.S;
             if (location == -1) return 0;
             return &S->node[location].data;
             }
      T* Next()
            {if (location == -1) return 0;
             location = S->node[location].link;
             if (location == -1) return 0;
             return &S->node[location].data;
             }
   private:
      SimSpace<T> *S;  // pointer to simulated space for chain
      int location;    // node index in simulated space
};
 
#endif
