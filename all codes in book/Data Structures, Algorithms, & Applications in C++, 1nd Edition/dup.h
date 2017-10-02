while (p) {
   q = p;
   if (e <= p->data) p = p->LeftChild;
   else p = p->RightChild;
   }
