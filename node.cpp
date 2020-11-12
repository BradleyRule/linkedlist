#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

Node::Node() {
  student = NULL;
  next = NULL;
}

Node::~Node(){
  delete &student;
  next = NULL;
}

void Node::setStudent(Student* newstudent) {
  student = newstudent;
}

Student* Node::getStudent(){
  return student;
}

void Node::setNext(Node* newnext){
  next = newnext;
}

Node* Node::getNext() {
  return next;
}
