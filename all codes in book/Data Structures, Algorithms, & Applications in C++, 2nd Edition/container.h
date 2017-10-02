// container struct used greedyLoading

#ifndef container_
#define container_

struct container
{
      int id, weight;
      operator int () const {return weight;}
};

#endif
