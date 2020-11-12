#include <iostream>
#include <cstring>
#include "node.h"
#include "student.h"

using namespace std;

//declaring functions
void createStudent(Node*&);
void deleteNode(Node*, Node*, Node*&, int);
void addStudent(Student*, Node*&, Node*, Node*);
void print(Node*);
void average(Node*, int, float);

//creating the head node of the list
Node* head = NULL;

int main(){
  //keeps the program running while true
  bool inuse = 1;
  //input for command
  char input[20];
  //input for delete function
  int id = 0;


  while(inuse == 1){//while theprogram is in use...
    //get the user input for what command they want to execute
    cout << "What would you like to do? (Commands: ADD, PRINT, DELETE, AVERAGE, QUIT)" << endl;
    cin.get(input, 20);
    cin.get();
    
    if (strcmp(input, "ADD") == 0){//if input is ADD run add function
      createStudent(head);
    }

    else if(strcmp(input, "PRINT") == 0){//if input is PRINT run print function
      print(head);
    }

    else if(strcmp(input, "DELETE") == 0){//if input is DELETE get id of student and run delete function
      cout << "enter the ID of the student you would like to remove:" << endl;
      cin >> id;
      cin.get();
    
      deleteNode(head, head, head, id);
      //reset input
      id = 0;
    }

    else if(strcmp(input, "QUIT") == 0){//if input is QUIT exit the program
      inuse = 0;
    }

    else if(strcmp(input, "AVERAGE") == 0){//if input is AVERAGE run average function
      average(head, 0, 0);
    }
    
    for (int i = 0; i <= 20; i++){//reset the input
      input[i] = '\0';
    }
  }
  
  
  return 0;
}


void createStudent(Node* &head){
  // this function get a first and last name as well as gpa and id number
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
  
  //this information is added to a new student pointer below
  Student* newstudent = new Student(first);
  newstudent->setLastName(last);
  newstudent->setID(id);
  newstudent->setGPA(gpa);
  
  //this data will then be passed into the addStudent function 
  Node* previous = head;
  Node* current = head;
  addStudent(newstudent, head, current, previous);
}

void addStudent(Student* newstudent, Node* &head, Node* current, Node* previous){
  if (head == NULL){//if there is nothing in the list
    //create a new node, add the student to the node and set the head pointer to the node
    Node* newnode = new Node();
    newnode->setStudent(newstudent);
    head = newnode;
  }
  //if the end of the list is reached or the next id in the list is bigger than the one being added
  else if (current == NULL || current->getStudent()->getID() >= newstudent->getID()){
    if(current == head){//if the node being added will replace one that is set as the head
      //create a new node, add the student and set it as the head then set previous(what was previously the head) to next
      Node* newnode = new Node();
      newnode->setStudent(newstudent);
      newnode->setNext(current);
      head = newnode;
    }
    else if (current != head){//if the node being replaced is not the head
      //create the new node with student
      Node* newnode = new Node();
      newnode->setStudent(newstudent);
      //set the current node (it is either null or has an id greater than the new student) to the next node of the new node
      newnode->setNext(current);
      //make sure the previous node points to the new node
      previous->setNext(newnode);
    }
    
  }
  else if(current != NULL){//if current is not null and does not have an id greater than the new student
    //run addStudent again passing in the same new student but advancing current and previous by one position in the list
    addStudent(newstudent, head, current->getNext(), current);
  }
}

void deleteNode(Node* current, Node* previous, Node* &head, int id){//deletes the selected node

  if(head != NULL){//if there are students in the list
    if(current == NULL){//if the current node is NULL tell user they have reached the end of the list and not found a match
      cout << "The ID you entered doesn't match any in the database" << endl;
    }
    else if(current->getStudent()->getID() == id){//if the id matches what they were looking for
      if(current == head){//if the node is the head pointer
	//set the head equal to the next node
	head = current->getNext();
	//delete the current node
	delete current;
	current = NULL;
      }
      else if(current != head){//if the node being deleted is not the head
	//make the previous pointer point to the node after the one that is being deleted
	previous->setNext(current->getNext());
	//delete the current node
	delete current;
	current = NULL;
      }
    }
    else if(current->getStudent()->getID() != id){//if the ids do not match
      //rerun the method and advance previous and current by one position in the list
      deleteNode(current->getNext(), current, head, id);
    }
  }
  else if (head == NULL){//if there is nothing in the list
    cout << "There are no students to delete" << endl;
  }
}

void average(Node* current, int count, float total){//this method prints the average gpa of all students in the list
  if(current != NULL){// if the current node is not null
    //increase the count by one, add the gpa of the current student to the total and run the method again passing in
    //the updated count, total and next node in the list
    count += 1;
    total += current->getStudent()->getGPA();
    average(current->getNext(), count, total);
  }
  else if(current == NULL){//when the end of the list is reached
    if(count != 0){//if there was 1 or more students in the list
      //calculate the average
      float average = (float)(total/count);
      //print out what the average is
      cout << "The average GPA of all the students is: ";
      cout.precision(3);
      cout << average << endl;
      
    }
    else if(count == 0){//if there were no students in the list, tell the user
      cout << "There are no students listed" << endl;
    }
  }
}

void print(Node* next){//this method prints out the entire list of students including their first and last name as well as gpa and id
  if (next == head){//start by entering a blank line to create space in the terminal
    cout << "" << endl;
  }
  if (next != NULL){//if the end has not been reached...
    //print out the first and last name and id of the current node
    cout << next->getStudent()->getFirstName() << " " << next->getStudent()->getLastName() << ", " << next->getStudent()->getID() << ", ";
    //adjust the precision
    cout.precision(3);
    //print out the gpa
    cout << next->getStudent()->getGPA() << endl;
    //run the print method again on the next node in the list
    print(next->getNext());
  }
  else if(next == NULL){//if the end is reached, print out a blank line to create space in the terminal
    cout << endl;
  }
}
