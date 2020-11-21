#include <iostream>
#include "GenDoublyLinkedList.h"

using namespace std;

template <class T>
class GenQueue{
  public:
    GenQueue();
    ~GenQueue();

    void insert(T elem);
    T remove();
    T peekFront();
    T peekBack();
    bool isEmpty();
    int getSize();

  private:
    int numElem;
    GenDoublyLinkedList<T> *myQueue;
};

template <class T> //constructor
GenQueue<T>::GenQueue(){
  myQueue = new GenDoublyLinkedList<T>();
  numElem = 0;
}

template <class T> //deconstructor
GenQueue<T>::~GenQueue(){
  delete myQueue;
}

template <class T> //insert
void GenQueue<T>::insert(T elem){
  myQueue->insertBack(elem);
  numElem++;
}

template <class T> //remove and removefront
T GenQueue<T>::remove(){
  if(isEmpty()){
    cout<< "Error! Empty Queue!"<<endl;
  }
  myQueue->removeFront();
  numElem--;
}

template <class T> //peek front
T GenQueue<T> ::peekFront(){
  return myQueue->front->data;
}

template <class T> //peek back
T GenQueue<T>::peekBack(){
  return myQueue->back->data;
}

template <class T> //checks if empty
bool GenQueue<T>::isEmpty(){
  if(numElem <= 0){
    return true;
  }
  else{
    return false;
  }
}

template <class T> //returns number of elements 
int GenQueue<T>::getSize(){
  return numElem;
}
