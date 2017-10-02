// node type used by winner tree

#ifndef player_
#define player_

struct player
{
   int id, key;

   operator int () const {return key;}
};

#endif
