// abstract class dictionary
// abstract data type specification for dictionary data structure
// all methods are pure virtual functions
// K is key type and E is value type

#ifndef dictionary_
#define dictionary_

using namespace std;

template<class K, class E>
class dictionary 
{
   public:
      virtual ~dictionary() {}
      virtual bool empty() const = 0;
                  // return true iff dictionary is empty
      virtual int size() const = 0;
                  // return number of pairs in dictionary
      virtual pair<const K, E>* find(const K&) const = 0;
                  // return pointer to matching pair
      virtual void erase(const K&) = 0;
                  // remove matching pair
      virtual void insert(const pair<const K, E>&) = 0;
                  // insert a (key, value) pair into the dictionary
};
#endif

