#include "Node.h"

Node::Node(Contact_Person* Contacts) { //Constructor takes a pointer object
    this->Contacts = Contacts;
    next = nullptr;
}