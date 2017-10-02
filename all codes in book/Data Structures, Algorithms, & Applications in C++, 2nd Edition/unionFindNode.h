// nodes used in union/find trees

#ifndef unionFindNode_
#define unionFindNode_

using namespace std;


struct unionFindNode
{
   int parent;  // if true then tree weight
                // otherwise pointer to parent in tree
   bool root;   // true iff root

   unionFindNode()
      {parent = 1; root = true;}
};
#endif;
