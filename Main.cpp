#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "GenQueue.h"
#include "Window.h"


int main(int argc, char** argv) {
  GenQueue<Student*> *q = new GenQueue<Student*>(); //students in line or window
  GenQueue<Student*> *endQueue = new GenQueue<Student*>(); //end of line or window

  int time = 0;
  string file = "";
  int numStudents = 0;
  int overFiveMin = 0;
  int numWindows = 0;
  int clockTime = 0;
  int overTenMin = 0;
  float waitTime = 0;
  float idleTime = 0;
  bool makeStu = true;

  //file in command line argument, index 1
  if(argc == 1) {
    cerr << "Error! No file entered. Please enter file name in command line!" << endl;
    exit(1);
  }
  else {
    file = argv[1];
  }

  //open and read user entered file
  ifstream inFile (file);
  string line;
  vector<int> input;
  int lineInput;
  if(inFile.is_open()) {
    while(getline(inFile, line)) {
      try {
        lineInput = stoi(line);
        input.push_back(lineInput);
      }
      catch(std::invalid_argument) {
        cout << "Error! File may only have numbers. Please re-enter a file!" << endl;
        exit(1);
      }
    }
  }
  else {
    cerr << "Error! File did not open." << endl;
    exit(1);
  }
  inFile.close();

  //makes students, add to  queue
  while(makeStu == true) {
    for(int i = 1; i < input.size(); ++i) {
      time = input[i];
      numStudents = input[i+1];
      for(int j = i+2; j < i+numStudents+2; ++j) {
        Student *s1 = new Student();
        s1->windowTime = input[j];
        s1->arrivalTime = time;
        q->insert(s1);
      }
      i += (numStudents+1); //continues adding students
    }
    makeStu = false;
  }

  //makes windows using Array
  numWindows = input[0];
  Window *windowArr[numWindows];
  for(int i = 0; i < numWindows; ++i) {
    Window *w1 = new Window(); //new window made
    windowArr[i] = w1;
  }

  //Main
  int queueSize = q->getSize();
  int stuWait[queueSize];
  while(!q->isEmpty()) {
    for(int i = 0; i < q->getSize(); ++i) {
      Student *tempStudent = q->peekFront();
      q->remove();
      if(tempStudent->arrivalTime == clockTime) {
        int notOpenWin = 0;
        for(int i = 0; i < numWindows; ++i) {
          if(tempStudent->isAtWindow == false && windowArr[i]->isOpen == true) {
            tempStudent->departTime = tempStudent->windowTime + clockTime; //assigns time to depart from window
            windowArr[i]->makeStudent(tempStudent);
          }
          else if(windowArr[i]->isOpen == false) { //adds together windows that are closed
            notOpenWin++;
            if(notOpenWin == numWindows) { //wait time in line
              tempStudent->updateWaitTime();
            }
          }
          else {
            continue; //continues because window is open and keeps track
          }
        }
      }
      else if(tempStudent->arrivalTime < clockTime && tempStudent->isAtWindow == false){ // stu is in line
        int notOpenWin = 0; //not open window
        for(int i = 0; i < numWindows; ++i){
          if(windowArr[i]->isOpen == true && tempStudent->isAtWindow == false) {
            tempStudent->departTime = tempStudent->windowTime + clockTime; //tells you when the student will depart
            windowArr[i]->makeStudent(tempStudent);
          }
          else if(windowArr[i]->isOpen == false) { //window is not open
            notOpenWin++;
            if(notOpenWin == numWindows) {
              tempStudent->updateWaitTime(); //updates wait time for student while window is closed
            }
          }
        }
      }
      if(tempStudent->departTime == clockTime) //makes sure studen is not there for longer than time
        endQueue->insert(tempStudent); //inserted at the end because they finished/departed window
      else
        q->insert(tempStudent);
    }
    if(q->isEmpty() == false){ //changes time if the queue is not empty
      for(int i = 0; i < numWindows; ++i) {
        windowArr[i]->updateWindow();
      }
      clockTime++;
    }
  }

 for(int i = 0; i < queueSize; ++i) {
   Student *studentStats = endQueue->peekFront();
    endQueue->remove();
   stuWait[i] = studentStats->waitTime;
 }

 // mean total wait time and those over 10 minutes
 for(int i = 0; i < queueSize; ++i) {
   waitTime += stuWait[i];
   if(stuWait[i] > 10)
    overTenMin++;
 }
 // median student wait time
 float medianSWait = 0;
 if(queueSize%2 == 0)
  medianSWait = (stuWait[(queueSize/2)] + stuWait[(queueSize/2)-1]) / 2.0;
 else
  medianSWait = stuWait[(queueSize/2)+1];

  //mean window idle time
  for(int i = 0; i < numWindows; ++i) {
    idleTime += windowArr[i]->openTime;
    if(windowArr[i]->openTime > 5)
      overFiveMin++;
  }

 int idleTimeArr[numWindows];
 for(int i = 0; i < numWindows; ++i) {
   idleTimeArr[i] = windowArr[i]->openTime;
}

//output the info
 cout << "Registrar's Office Information: " << endl;
 cout << "1. The mean student wait time is: " << waitTime/queueSize << " minutes." << endl;
 cout << "2. The median student wait time is: " << medianSWait << " minutes." << endl;
 cout << "3. The longest student wait time is: " << stuWait[queueSize-1] << " minutes." << endl;
 cout << "4. The number of students with wait times over 10 minutes is:  " << overTenMin << " students." << endl;
 cout << "5. The mean window idle time is:  " << idleTime/numWindows << " minutes." <<endl;
 cout << "6. The longest window idle time is: " << idleTimeArr[numWindows-1] <<  " minutes." << endl;
 cout << "7. The number of windows idle for over 5 minutes is: " << overFiveMin << endl;
}
