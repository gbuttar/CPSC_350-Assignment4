#include <iostream>
#include "ListNode.h"

using namespace std;

template <class T>
class GenDoublyLinkedList{

public:
  ListNode<T> *front;
  ListNode<T> *back;
  unsigned int size;

  GenDoublyLinkedList(); //constructor
  ~GenDoublyLinkedList(); //deconstructor

  void insertFront(T data);
  void insertBack (T data);
  T removeFront();
  T removeBack();
  T search(T sElem);
  T remove (T rElem);
  T removeAt(int pos);


  unsigned int getSize();
  bool isEmpty();
  void printList();
};

template <class T> //constructor
GenDoublyLinkedList<T>::GenDoublyLinkedList(){
  size = 0;
  front = NULL;
  back = NULL;
}

template <class T> //deconstructor
GenDoublyLinkedList<T>::~GenDoublyLinkedList(){
}

template <class T>
void GenDoublyLinkedList<T>::insertFront(T elem){
  ListNode<T> *node = new ListNode<T>(elem);
  if(size ==0)
    back = node;
  else{
    node->next = front;
    front->prev = node;
  }
  front = node;
  size++;
}
template <class T>
void GenDoublyLinkedList<T>::insertBack(T elem){
  ListNode<T> *node = new ListNode<T>(elem);
  if(size == 0){
    front = node;
  }
  else{
    back->next = node;
    node->prev = back;
  }
  back = node;
  size++;
}

template <class T>
T GenDoublyLinkedList<T>::removeFront(){
  T temp = front->data;
  ListNode<T> *f = front;
  front = front->next;
  f->next = NULL;
  delete f;
  size--;
  return temp;
}

template <class T>
T GenDoublyLinkedList<T>::removeBack(){
  T temp = back->data;
  ListNode<T> *b = back;
  back = back->prev;
  back->next = NULL;
  b->prev = NULL;
  delete b;
  size--;
  return temp;
}

//searches
template <class T>
T GenDoublyLinkedList<T>::search(T s){
  int position = -1;
  ListNode<T> *curr = front;
  while(curr != NULL){
    position++;
    if(curr->data == s){
      break;
    }
    else{
      curr = curr->next;
    }
  }
  if(curr == NULL){
    position = -1;
  }
  return position;
}

//removes at given position
template <class T>
T GenDoublyLinkedList<T>::removeAt(int pos){
  int index =0;
  if (pos < size){
    ListNode<T> *curr = front;
    ListNode<T> *prev = front;
  while(index !=pos){
    prev = curr;
    curr = curr->next;
    index++;
  }
  if(index == pos){
    prev->next = curr->next;
    curr->next = NULL;
    curr->prev = NULL;
    T temp = curr->data;
    delete curr;
    size--;
    return temp;
  }
}
}

//checks if empty
template <class T>
bool GenDoublyLinkedList<T>::isEmpty(){
  if(size > 0){
    return false;
  }
  else{
    return true;
  }
}
//get the size
template <class T>
unsigned int GenDoublyLinkedList<T>::getSize(){
  return size;
}


//removes
template<class T>
T GenDoublyLinkedList<T>::remove(T val){
  if(size == 0){
    return -1;
  }
  ListNode<T> *curr = front;
  while(curr->data != val) {
    curr = curr->next;
    if(curr == NULL){
      return -1;
    }
  }
  if(curr == front){
    front = curr->next;
  }
  else if(curr == back){
    back = curr->prev;
  }
  else {
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
  }
  curr->next = NULL;
  curr->prev = NULL;
  size--;
  return curr->data;
}

//printing
template <class T>
void GenDoublyLinkedList<T>::printList(){
  ListNode<T> *curr = front;
  while(curr != NULL){
    cout<< curr->data<<endl;
    curr = curr->next;
  }
}
