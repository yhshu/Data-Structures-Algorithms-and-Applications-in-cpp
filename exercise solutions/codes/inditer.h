
// indirect list iterator

#ifndef IndirectListIterator_
#define IndirectListIterator_

template<class T>
class IndirectListIterator {
   public:
      T* Initialize(const IndirectList<T>& c)
             {if (c.length > 0) {// nonempty list
                                 length = c.length;
                                 table = c.table;
                                 location = 0;
                                 return table[0];
                                 }
              // empty list
              location = 0;
              return 0;}
      T* Next()
            {if (location >= length) return 0;
             location++;
             return table[location];}
   private:
      int location;  // current position in list
      int length;    // list length
      T **table;     // array of pointers
};
 
#endif
