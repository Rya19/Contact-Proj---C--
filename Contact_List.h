#ifndef CONTACT_LIST_H
#define CONTACT_LIST_H

#include "Node.h"
#include <string>

using namespace std;

class Contact_List {
    private:
        Node* head; //The start of the linked list

    public:
        Contact_List();
        ~Contact_List(); //Need this explained

        //Analogy: Placing an item on a shelf, the old front item moves back one space
        void AddContact(Contact_Person* contact); 
        
        void displayAll() const; 
        void saveToFile(const string& File_Name) const; 
        void LoadFromFile(const string& FileName);
        bool DeleteByName(const string& NameToDelete);
        void SearchByName(const string& NameToSearch) const;
        bool EditContacts(const string& nameToEdit);
        void sortByLastName();
};

#endif