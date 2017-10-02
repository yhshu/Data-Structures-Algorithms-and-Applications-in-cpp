// exception classes for various error types

#ifndef Xcept_
#define Xcept_

#include <new.h>

// bad initializers
class BadInitializers {
   public:
      BadInitializers() {}
};

// insufficient memory
class NoMem {
   public:
      NoMem() {}
};

// change new to throw NoMem instead of standard behavior
// Visual C++ requires following form of my_new_handler
int my_new_handler(size_t x)
{
   throw NoMem();
   // even though the following statement is unreachable,
   // visual C++ will not compile successfully without it
   return 0;
};

_PNH Old_Handler_ = _set_new_handler(my_new_handler);

// improper array, find, insert, or delete index
// or deletion from empty structure
class OutOfBounds {
   public:
      OutOfBounds() {}
};

// use when operands should have matching size
class SizeMismatch {
   public:
      SizeMismatch() {}
};

// use when zero was expected
class MustBeZero {
   public:
      MustBeZero() {}
};

// use when zero was expected
class BadInput {
   public:
      BadInput() {}
};

#endif

