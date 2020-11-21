template <class T>

class ListNode{
  public:
    T data;
    ListNode *prev;
    ListNode *next;

  ListNode();
  ListNode(T element);
  ~ListNode();
};

template <class T> //constructor
ListNode<T>::ListNode() {
  data = NULL;
  next = NULL;
  prev = NULL;
}

template <class T> //overloaded
ListNode<T>::ListNode(T element) {
  data = element;
  next = NULL;
  prev = NULL;
}

template <class T> //deconstructor
ListNode<T>::~ListNode(){
  next = NULL;
  prev = NULL;
}
