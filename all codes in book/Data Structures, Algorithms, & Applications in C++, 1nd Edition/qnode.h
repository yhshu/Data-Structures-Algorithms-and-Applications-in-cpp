// used by bbloadc.cpp

#ifndef QNode_
#define QNode_

template<class T>
class  QNode {
   friend void AddLiveNode(LinkedQueue<QNode<T>*> &, T,
      int, int, T, QNode<T> *, QNode<T> *&, int *, bool);
   friend T MaxLoading(T *, T, int, int *);
   private:
      QNode *parent; // pointer to parent node
      bool LChild;   // true iff left child of parent
      T weight;      // weight of partial solution
                     // defined by path to this node
};

#endif
