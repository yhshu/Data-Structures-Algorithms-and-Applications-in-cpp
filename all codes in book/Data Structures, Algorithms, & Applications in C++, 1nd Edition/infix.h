template <class T>
void Infix(BinaryTreeNode<T> *t)
{// Output infix form of expression.
   if (t) {cout << '(';
           Infix(t->LeftChild);  // left operand
           cout << t->data;      // operator
           Infix(t->RightChild); // right operand
           cout << ')';}
}
