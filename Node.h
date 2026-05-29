#ifndef NODE_H
#define NODE_H

#include "Contact_Person.h"

class Node {
    public:
        //This is a pointer bc the Contacts pointer can point to any of its subclass
        Contact_Person* Contacts; //A pointer to a contact, can be PC or BC. This can point to ANY contact type & can dynamically call the correct overriden function
        Node* next; //points to next node in list

        //Constrcutor
        Node(Contact_Person* Contacts);
};

#endif