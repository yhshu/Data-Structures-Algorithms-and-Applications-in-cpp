// abstract class binary tree
// abstract data type specification for binary trees
// all methods are pure virtual functions
// T is node type

#ifndef binaryTree_
#define binaryTree_

#include <functional>

using namespace std;

template<class T>
class binaryTree 
{
   public:
      virtual ~binaryTree() {}
      virtual bool empty() const = 0;
      virtual int size() const = 0;
      virtual void preOrder(void (*) (T *)) = 0;
              // parameter is a pointer to a function whose return
              // type is void and has a single argument of type T*
      virtual void inOrder(void (*) (T *)) = 0;
      virtual void postOrder(void (*) (T *)) = 0;
      virtual void levelOrder(void (*) (T *)) = 0;
};
#endif

