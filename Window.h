#include <iostream>
#include "Student.h"

using namespace std;

class Window{
public:
  Student *stu;
  bool isOpen;
  int openTime;

  Window();
  ~Window();

  void makeStudent(Student *stu1);
  Student* removeStudent();
  void updateWindow();

};

Window::Window(){ //constructor
  isOpen = true;
  openTime = 0;
  stu = NULL;
}

Window::~Window(){  //deconstructor
}

void Window::makeStudent(Student *stu1){ //creates student
  stu = stu1;
  isOpen = false;
  stu->isAtWindow = true;
}

Student Window::removeStudent(){ //removes student
  Student *stu1 = stu;
  stu = NULL;
  isOpen = true;
  return *stu1;
}

void Window::updateWindow(){ //changes window
  if(isOpen == true){
    openTime++;
  }
  else{
    stu->windowTime--;
    if(stu->windowTime == 0){
      removeStudent();
    }
  }
}
