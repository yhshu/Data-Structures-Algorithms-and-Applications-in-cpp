
// Extension of chain to include a method to erase by matching element field
// This class is for use by the linked graph classes

#ifndef graphChain_
#define graphChain_

#include "chainWithIterator.h"
#include "chainNode.h"

using namespace std;


template <class T>
class graphChain : public chain<T>
{
   public: 
      T* eraseElement(int theVertex)
      {// Delete node with element == theVertex. Return pointer to
       // deleted element. Return NULL if no matching element.
         chainNode<T> *current = firstNode,
                      *trail = NULL; // one behind current
      
         // search for match
         while (current != NULL && current->element != theVertex)
         {
            trail = current;
            current = current->next;
         }
   
         if (current == NULL) // no match
            return NULL;
      
         // match found in node current
         T* theElement = &current->element; // save matching element
      
         // remove current from chain
         if (trail != NULL)
            trail->next = current->next;
         else
            firstNode = current->next; // current is first node
      
         delete current;
         listSize--;
         return theElement;
      }
};
#endif
