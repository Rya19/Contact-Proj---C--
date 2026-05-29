#include "Contact_List.h"
#include "PersonalContact.h"
#include "BusinessContact.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

Contact_List::Contact_List() { //Constructor sets head to nothing
    head = nullptr;
}

void Contact_List::AddContact(Contact_Person* contact) { //Adds contact to front of list; Takes a pointer bc in menu option, it takes either PC or BC. Lets you write A single LL that allows for different contacts.
    Node* newNode = new Node(contact); //create a node object and save it as a node object of a contact type
    newNode->next = head; //This node's next now points to what the head was pointing to 
    head = newNode; //the head is now the newnode 

    //**IMPORTANT**: The head is just there to tell you what the first item in the LL is, it doesn't store a value, just the "next"
}

void Contact_List::displayAll() const { //This is a read-only function, the func will not modify any member variables of the class.
    Node* current = head; //Create a node that points to the head, this is used for traversing through
    while (current != nullptr) { //keep going until we reached a nullptr
        current->Contacts->display(); //uses polymorphism to display the correct type of display for the specific contact
        cout << "----------------------\n";
        current = current->next; //move to the next one continuously until while loop stops
    }
}

void Contact_List::saveToFile(const string& File_Name) const { //adding & avoids making copies of the string, saves memory & time. const to make function avoid making changes to it. (Func is receiving a string, not gonna copy it or make changes to it). Good for func inputs that are "read only"
    ofstream outFile(File_Name); //ofstream is a type, outFile is a variablename of that type, file_name is the file passed through it

    if (!outFile) {
        cerr << "Error opening the file, perhaps mis-input?\n";
        return;
    }
    else {
        Node* current = head; //Similar to display function
        while (current != nullptr) {
            outFile << current->Contacts->toString() << endl; //loop through all the Vector_Nodes and put each contact into the file
            current = current->next;
        }

        outFile.close();
    }
}

void Contact_List::LoadFromFile(const string& FileName) {
    ifstream in_File(FileName);
    if (!in_File) {
        cerr << "Error opening file for reading, perhaps mistyped file?\n";
        return;
    }
    else {
        string Current_Line;
        while (getline(in_File, Current_Line)) { //getLine reads an entire line instead of just a word; While this file has lines to read:
            istringstream IStrStrm(Current_Line); //strstream obj used for reading from stream strings. you can pull out each piece that is seperated by a comma.
            string Contact_Type; //Keeps track of hte type of contact that comes up
            getline(IStrStrm, Contact_Type, ',');

            string Contact_Name, Contact_PhoneNumber, Contact_Email;
            getline(IStrStrm, Contact_Name, ','); //seperate w/ ,
            getline(IStrStrm, Contact_PhoneNumber, ',');
            getline(IStrStrm, Contact_Email, ',');

            if (Contact_Type == "P-C") { //Function will determine what type of contact it is
                string Contact_Birthday;
                getline(IStrStrm, Contact_Birthday); //Along with getting the name, pn, email, itll get the bday if its P-C type
                Contact_Person* PC = new PersonalContact(Contact_Name, Contact_PhoneNumber, Contact_Email, Contact_Birthday); //PC = personal contact
                //Creates a new Pc object on the heap, its memory address is returned and stored in the pointer. Its then added to the LL with the func below.
                AddContact(PC);
            }
            else if (Contact_Type == "B-C") {
                string Contact_Company, Contact_Position;
                getline(IStrStrm, Contact_Company, ',');
                getline(IStrStrm, Contact_Position, ',');

                Contact_Person* BC = new BusinessContact(Contact_Name, Contact_PhoneNumber, Contact_Email, Contact_Company, Contact_Position);
                AddContact(BC);
            }
        }
        in_File.close();
    }
}

bool Contact_List::DeleteByName(const string& NameToDelete) { //takes a string reference
    Node* current = head; //current points to the address of head (if LL empty, then  points to nullptr)
    Node* previous = nullptr; //Nothing is behind previous, just a nullptr (before the function starts); no node before the head.

    while (current != nullptr) {
        if (current->Contacts->getContact_Name() == NameToDelete) { //if current contact name matches the one to remove:
            if (previous == nullptr) { //if previous is nullptr, this means we are deleting the first node in the LL. So move head to the second node in LL.
                head = current->next; //points to 2nd node in LL, that will be the new head (if it exists)
            }
            else { //if yure somewhere in the middle of the list (not end or beginning of LL), make prev node skip over the current node.
                previous->next = current->next; //node previous points to what current is pointing to
            }

            delete current->Contacts; //??
            delete current;
            return true;
        }

        previous = current;
        current = current->next;
    }

    return false; //Unable to find name
}

void Contact_List::SearchByName(const string& NameToSearch) const {
    Node* current = head; // Current points to whatever head is pointing to (address-wise)

    while (current != nullptr) {
        if (current->Contacts->getContact_Name() == NameToSearch) {
            current->Contacts->display();
            return; //get out of loop
        }
        current = current->next; //keep going
    }

    cout << "Contact noneistent.\n";
}

bool Contact_List::EditContacts(const string& nameToEdit) {
    Node* current = head;

    while (current != nullptr) {
        if (current->Contacts->getContact_Name() == nameToEdit) {
            cout << "Contact found. Current details:\n";
            current->Contacts->display(); //Gives the current details of the contact you inputted

            cout << "\nEnter new name: ";
            string newName;
            getline(cin, newName); //gets entire name including spaces

            cout << "Enter new phone: ";
            string newPhone;
            getline(cin, newPhone);

            cout << "Enter new email: ";
            string newEmail;
            getline(cin, newEmail);

            current->Contacts->setContact_Name(newName);
            current->Contacts->setContact_PhoneNumber(newPhone);
            current->Contacts->setContact_Email(newEmail);

                                                                    //Safe to treat current->Contacts as a PC, or BC
            if (PersonalContact* pc = dynamic_cast<PersonalContact*>(current->Contacts)) { //dynamic cast converts Contacts to PersonalContact; Trying to convert base class pointer to PC pointer. 
                cout << "Enter new birthday: ";
                string bday;
                getline(cin, bday);

                pc->setBirthday(bday);
            } 
            else if (BusinessContact* bc = dynamic_cast<BusinessContact*>(current->Contacts)) {
                cout << "Enter new company: ";
                string company;
                getline(cin, company);
                
                cout << "Enter new position: ";
                string position;
                getline(cin, position);

                bc->setContact_CompanyName(company);
                bc->setContact_JobTitle(position);
            }

            return true;
        }

        current = current->next; //Loop through and find the contact
    }

    return false;
}

void Contact_List::sortByLastName() {
    if (!head || !head->next) { //If head empty or only 1 node exists in LL
        return;
    }

    vector<Node*> Vector_Nodes; //Store Vector_Nodes in vector to sort easily

    Node* current = head;
    while (current != nullptr) {
        Vector_Nodes.push_back(current); //go through list and put all elements in LL into the vector
        current = current->next;
    }//We did this to use the sort function/method.

  //   
    sort(Vector_Nodes.begin(), Vector_Nodes.end(), [](Node* a, Node* b) { //(Start of vector, End of vector, lambda func that compares two node pointers)
        string nameA = a->Contacts->getContact_Name(); //Gets the full name
        string nameB = b->Contacts->getContact_Name();

        string lastA = nameA.substr(nameA.find_last_of(' ') + 1); //Finds the posiiton of the last space in the name and then grabs only the last name
        string lastB = nameB.substr(nameB.find_last_of(' ') + 1);

        return lastA < lastB;
    });

    for (size_t i = 0; i < Vector_Nodes.size() - 1; ++i) {
        Vector_Nodes[i]->next = Vector_Nodes[i + 1]; //Each node's next will pooint to the next sorted node in the vector
    }

    Vector_Nodes[Vector_Nodes.size() - 1]->next = nullptr; //The end of the vector points to nullptr (nothing)
    head = Vector_Nodes[0]; //Head is the beginning of the vector
}

//Need this explained
Contact_List::~Contact_List() {
    Node* current = head; //current points to whatever the head is pointing to

    while(current != nullptr) { //used to keep going through the end to the LL
        Node* next = current->next; //new node created to save pointer to the next node before deleting the current, so you dont lose the link
        delete current->Contacts; //deletes contact object that the node is pointing to
        delete current; //delete the node itself

        current = next; //move to the next node in the LL
    } //Rinse and repeat this.
}