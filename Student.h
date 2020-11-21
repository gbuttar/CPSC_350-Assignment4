#include <iostream>

using namespace std;

class Student{
  public:
    int arrivalTime;
    int waitTime;
    int departTime;
    int windowTime;
    bool isAtWindow;

    Student();
    ~Student();
    Student(int windowTime);

    void updateWindowTime();
    void updateWaitTime();
};

Student::Student(){ //constructor
  arrivalTime = 0;
  waitTime = 0;
  departTime = -1;
  windowTime = 0;
  isAtWindow = false;
}

Student::~Student(){ //deconstructor
}

Student::Student(int windowTime) {
  windowTime = windowTime;
  arrivalTime = 0;
  waitTime = 0;
}

void Student::updateWindowTime() {
  windowTime--; //lessen total window time
}

void Student::updateWaitTime() {
  waitTime++; //increase wait time
}
