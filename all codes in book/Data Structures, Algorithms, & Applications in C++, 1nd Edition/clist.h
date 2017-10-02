template<class T>
int CircularList<T>::Search(const T& x) const
{// Locate x in a circular list with head node.
   ChainNode<T> *current = first->link;
   int index = 1; // index of current
   first->data = x; // put x in head node

   // search for x
   while (current->data != x) {
      current = current->link);
      index++;
      }

   // are we at head?
   return ((current == first) ? 0 : index);
}
