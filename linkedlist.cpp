#include <iostream>
#include <cstring>
#include "node.h"
#include "student.h"

using namespace std;

void createStudent(Node*&);
void deleteNode(Node*, Node*, Node*&, int);
void addStudent(Student*, Node*&, Node*, Node*);
void print(Node*);
void average(Node*, int, float);

Node* head = NULL;

int main(){
  bool inuse = 1;
  char input[20];
  int id = 0;


  while(inuse == 1){
    cout << "What would you like to do? (Commands: ADD, PRINT, DELETE, AVERAGE, QUIT)" << endl;
    cin.get(input, 20);
    cin.get();
    
    if (strcmp(input, "ADD") == 0){
      createStudent(head);
    }

    else if(strcmp(input, "PRINT") == 0){
      print(head);
    }

    else if(strcmp(input, "DELETE") == 0){
      cout << "enter the ID of the student you would like to remove:" << endl;
      cin >> id;
      cin.get();
    
      deleteNode(head, head, head, id);
      id = 0;
    }

    else if(strcmp(input, "QUIT") == 0){
      inuse = 0;
    }

    else if(strcmp(input, "AVERAGE") == 0){
      average(head, 0, 0);
    }
    
    for (int i = 0; i <= 20; i++){
      input[i] = '\0';
    }
  }
  
  
  return 0;
}


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

  Node* previous = head;
  Node* current = head;
  addStudent(newstudent, head, current, previous);
}

void addStudent(Student* newstudent, Node* &head, Node* current, Node* previous){
  if (head == NULL){
    Node* newnode = new Node();
    newnode->setStudent(newstudent);
    head = newnode;
  }
  else if (current == NULL || current->getStudent()->getID() >= newstudent->getID()){
    if(current == head){
      Node* newnode = new Node();
      newnode->setStudent(newstudent);
      newnode->setNext(current);
      head = newnode;
    }
    else if (current != head){
      Node* newnode = new Node();
      newnode->setStudent(newstudent);
      newnode->setNext(current);
      previous->setNext(newnode);
    }
    
  }
  else if(current != NULL){
    addStudent(newstudent, head, current->getNext(), current);
  }
}

void deleteNode(Node* current, Node* previous, Node* &head, int id){

  if(head != NULL){
    if(current == NULL){
      cout << "The ID you entered doesn't match any in the database" << endl;
    }
    else if(current->getStudent()->getID() == id){
      if(current == head){
	head = current->getNext();
	current->~Node();
	//delete &current;
      }
      else if(current != head){
	previous->setNext(current->getNext());
	current->~Node();
	//delete &current;
      }
    }
    else if(current->getStudent()->getID() != id){
      deleteNode(current->getNext(), current, head, id);
    }
  }
  else if (head == NULL){
    cout << "There are no students to delete" << endl;
  }
}

void average(Node* current, int count, float total){
  if(current != NULL){
    count += 1;
    total += current->getStudent()->getGPA();
    average(current->getNext(), count, total);
  }
  else if(current == NULL){
    if(count != 0){
      float average = (float)(total/count);
      cout << "The average GPA of all the students is: ";
      cout.precision(3);
      cout << average << endl;
      
    }
    else if(count == 0){
      cout << "There are no students listed" << endl;
    }
  }
}

void print(Node* next){
  if (next == head){
    cout << "" << endl;
  }
  if (next != NULL){
    cout << next->getStudent()->getFirstName() << " " << next->getStudent()->getLastName() << ", " << next->getStudent()->getID() << ", ";
    cout.precision(3);
    cout << next->getStudent()->getGPA() << endl;
    print(next->getNext());
  }
  else if(next == NULL){
    cout << endl;
  }
}
