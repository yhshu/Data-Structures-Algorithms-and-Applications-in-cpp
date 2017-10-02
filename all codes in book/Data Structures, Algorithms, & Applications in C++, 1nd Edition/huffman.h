#ifndef Huffman_
#define Huffman_

template<class T>
class  Huffman {
   friend BinaryTree<int> HuffmanTree(T [], int);
   public:
      operator T () const {return weight;}
   private:
      BinaryTree<int> tree;
      T weight;
};

#endif
