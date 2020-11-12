#include <iostream>
#include <cstring>
#include "node.h"
#include "student.h"

using namespace std;

void createStudent(Node*);
void addStudent(Student*, Node*, Node*);
void print(Node*);

Node* head = NULL;

int main(){
  bool inuse = 1;
  char input[20];
  


  while(inuse == 1){
    cin.get(input, 20);
    cin.get();
    
    if (strcmp(input, "ADD") == 0){
      createStudent(head);
    }

    else if(strcmp(input, "PRINT") == 0){
      print(head);
    }

    else if(strcmp(input, "DELETE") == 0){
      
    }

    else if(strcmp(input, "QUIT") == 0){

    }

    else if(strcmp(input, "AVERAGE") == 0){

    }
    
    for (int i = 0; i <= 20; i++){
      input[i] = '\0';
    }
  }
  
  
  return 0;
}

//void deleteStudent(){

//}

void createStudent(Node* &head){
  char* first = new char[40];
  char* last = new char[40];
  int id = 0;
  float gpa = 0;
  cout << "Enter first name" << endl;
  cin.get(first, 40);
  cin.get();
  cout << "Enter last name" << endl;
  cin.get(last, 40);
  cin.get();
  cout << "Enter id number" << endl;
  cin >> id;
  cin.get();
  cout << "Enter gpa" << endl;
  cin >> gpa;
  cin.get();

  Student* newstudent = new Student(first);
  newstudent->setLastName(last);
  newstudent->setID(id);
  newstudent->setGPA(gpa);

  Node* current = head;
  addStudent(newstudent, head, current);
}

void addStudent(Student* newstudent, Node* &head, Node* current){
  if (head->getNext() == NULL){
    Node* newnode = new Node();
    newnode->setStudent(newstudent);
    head->setNext(newnode);
  }
  else if (current->getNext() == NULL || current->getNext()->getStudent()->getID() <= current->getStudent()->getID()){
    Node* newnode = new Node();
    newnode->setStudent(newstudent);
    newnode->setNext(current->getNext());
    current->setNext(newnode);
    
  }
  else if(current->getNext() != NULL){
    addStudent(newstudent, head, current->getNext());
  }
}


void print(Node* next){
  if (next == head){
    cout << "List: ";
  }
  if (next != NULL){
    cout << next->getStudent()->getFirstName() << " ";
    print(next->getNext());
  }
}
