//THIS CODE WAS DONE FOR PRACTICE ON LINKED LISTS, FILES, CLASSES, POLYMORPHISM, INHERITANCE AND STRING MANUPILATION

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
//
using namespace std;

//Base class
class Contact_Person {
    //Unaccessible to classes that don't inherit this class (Only you and your kids can access)
    protected:
        string Contact_Name;
        string Contact_PhoneNumber;
        string Contact_Email;

    //Accessible
    public:
        //Constructor
        Contact_Person(string Contact_Name, string Contact_PhoneNumber, string Contact_Email) {
            this->Contact_Name = Contact_Name;
            this->Contact_PhoneNumber = Contact_PhoneNumber;
            this->Contact_Email = Contact_Email;

            /*
            Can also use:

            Contact_Person(parameters) :
            parameter1(parameter1), parameter2(parameter2), ...
            
            */
        }

        //Default Constructor
        Contact_Person() {
            Contact_Name = "";
            Contact_PhoneNumber = "";
            Contact_Email = "";
        }


        //Virtual destructor (needed for inheritance)
        virtual ~Contact_Person() {
            //nothing here yet
        }
        //Analogy: If someone deletes a contact object, go down to each bit (trail) and delete everything linked to this object
        //With virtual destructors in different contact classes, it'll know which deconstructor to call
        //If a class is meant to be a base (will be inherited from others), and you usep ointers, always make destructor virtual


        //Set/get Functions
        void setContact_Name(string cn) {
            this->Contact_Name = cn;
        }

        string getContact_Name() const { //Const b/c this Member function (function inside a class) won't modify any variables of the class 
            return Contact_Name;
        }


        void setContact_PhoneNumber(string cpn) {
            this->Contact_PhoneNumber = cpn;
        }

        string getContact_PhoneNumber() const {
            return Contact_PhoneNumber;
        }
        

        void setContact_Email(string ce) {
            this->Contact_Email = ce; //can just do Contact_Email = ce
        }

        string getContact_Email() const {
            return Contact_Email;
        }


        //Other functions

        //To display (will be overwritten)
        //Pure virtual because analogy: we want inherited classes to make these functions itself, they must know how to do that, I wont implement that
        //If a derived class (child class) overrides this function, always call the derived version, not THIS version. Ensures correct func gets called at runtime
        //Func must be overriden by any subclass, no base implementation. Can't create objects of this class.
        virtual void display() const = 0;   

        //Format contact info to write to a file
        virtual string toString() const = 0;

};


class PersonalContact : public Contact_Person {
    private:
        string Contact_Birthday;

    public:
        PersonalContact(string Contact_Name, string Contact_PhoneNumber, string Contact_Email, string Contact_Birthday) : Contact_Person(Contact_Name, Contact_PhoneNumber, Contact_Email) {
            this->Contact_Birthday = Contact_Birthday;
        }


        // Override display()
        void display() const override {
            cout << "Personal Contact:" << endl;
            cout << "Name: " << Contact_Name << endl;
            cout << "Phone: " << Contact_PhoneNumber << endl;
            cout << "Email: " << Contact_Email << endl;
            cout << "Birthday: " << Contact_Birthday << endl;
        }

        // Override toString() for saving to a given file
        string toString() const override {
            return "P-C," + Contact_Name + "," + Contact_PhoneNumber + "," + Contact_Email + "," + Contact_Birthday;
        }

        // Getter and setter for birthday
        string getBirthday() const { 
            return Contact_Birthday; 
        }

        void setBirthday(string bday) { 
            Contact_Birthday = bday; 
        }

        // Destructor
        ~PersonalContact() {
            
        }
};

class BusinessContact : public Contact_Person {
private:
    string Contact_CompanyName;
    string Contact_JobTitle;

public:
    // Constructor
    BusinessContact(string Contact_Name, string Contact_PhoneNumber, string Contact_Email, string Contact_CompanyName, string Contact_JobTitle) : Contact_Person(Contact_Name, Contact_PhoneNumber, Contact_Email) // Call base class constructor
    {
        this->Contact_CompanyName = Contact_CompanyName;
        this->Contact_JobTitle = Contact_JobTitle;
    }

    // Override display() as usual
    void display() const override {
        cout << "Business Contact:" << endl;
        cout << "Name: " << Contact_Name << endl;
        cout << "Phone: " << Contact_PhoneNumber << endl;
        cout << "Email: " << Contact_Email << endl;
        cout << "Company: " << Contact_CompanyName << endl;
        cout << "Job Title: " << Contact_JobTitle << endl;
    }

    // Override toString() for saving to a given file as usual
    string toString() const override {
        return "B-C," + Contact_Name + "," + Contact_PhoneNumber + "," + Contact_Email + "," + Contact_CompanyName + "," + Contact_JobTitle;
    }

    // Getters and Setters
    string getContact_CompanyName() const { 
        return Contact_CompanyName; 
    }
    void setContact_CompanyName(string company) { 
        Contact_CompanyName = company; 
    }

    string getContact_JobTitle() const { 
        return Contact_JobTitle; 
    }
    void setContact_JobTitle(string title) { 
        Contact_JobTitle = title; 
    }

    // Destructor
    ~BusinessContact() {
        
    }
};


//------------------------------------------------------------------------


class Node {
    public:
        //This is a pointer bc the Contacts pointer can point to any of its subclass
        Contact_Person* Contacts; //A pointer to a contact, can be PC or BC. This can point to ANY contact type & can dynamically call the correct overriden function
        Node* next; //points to next node in list

        //Constrcutor
        Node(Contact_Person* Contacts) { //Constructor takes a pointer object
            this->Contacts = Contacts;
            next = nullptr;
        }


};

class Contact_List {
    private:
        Node* head; //The start of the linked list

    public:
        Contact_List() { //Constructor sets head to nothing
            head = nullptr;
        }

        //Analogy: Placing an item on a shelf, the old front item moves back one space
        void AddContact(Contact_Person* contact) { //Adds contact to front of list; Takes a pointer bc in menu option, it takes either PC or BC. Lets you write A single LL that allows for different contacts.
            Node* newNode = new Node(contact); //create a node object and save it as a node object of a contact type
            newNode->next = head; //This node's next now points to what the head was pointing to 
            head = newNode; //the head is now the newnode 

            //**IMPORTANT**: The head is just there to tell you what the first item in the LL is, it doesn't store a value, just the "next"
        }

        void displayAll() const { //This is a read-only function, the func will not modify any member variables of the class.
            Node* current = head; //Create a node that points to the head, this is used for traversing through
            while (current != nullptr) { //keep going until we reached a nullptr
                current->Contacts->display(); //uses polymorphism to display the correct type of display for the specific contact
                cout << "----------------------\n";
                current = current->next; //move to the next one continuously until while loop stops
            }
        }

        void saveToFile(const string& File_Name) const { //adding & avoids making copies of the string, saves memory & time. const to make function avoid making changes to it. (Func is receiving a string, not gonna copy it or make changes to it). Good for func inputs that are "read only"
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


        void LoadFromFile(const string& FileName) {
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

        bool DeleteByName(const string& NameToDelete) { //takes a string reference
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

        void SearchByName(const string& NameToSearch) const {
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

        
    bool EditContacts(const string& nameToEdit) {
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


    void sortByLastName() {
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
    ~Contact_List() {
        Node* current = head; //current points to whatever the head is pointing to

        while(current != nullptr) { //used to keep going through the end to the LL
            Node* next = current->next; //new node created to save pointer to the next node before deleting the current, so you dont lose the link
            delete current->Contacts; //deletes contact object that the node is pointing to
            delete current; //delete the node itself

            current = next; //move to the next node in the LL
        } //Rinse and repeat this.

    }

};

int main() {
    Contact_List contactList;
    string filename = "contacts.txt";
    int choice;

    do {
        cout << "\n====== Contact Manager ======\n";
        cout << "1. Add Personal Contact\n";
        cout << "2. Add Business Contact\n";
        cout << "3. View All Contacts\n";
        cout << "4. Search Contact by Name\n";
        cout << "5. Delete Contact by Name\n";
        cout << "6. Edit Contact by Name\n";
        cout << "7. Sort Contacts by Last Name\n";
        cout << "8. Save to File\n";
        cout << "9. Load from File\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // clear the newline character

        string name, phone, email, birthday, company, position;

        switch (choice) {
            case 1:
                cout << "Enter name: "; getline(cin, name);
                cout << "Enter phone: "; getline(cin, phone);
                cout << "Enter email: "; getline(cin, email);
                cout << "Enter birthday: "; getline(cin, birthday);
                contactList.AddContact(new PersonalContact(name, phone, email, birthday));
                break;

            case 2:
                cout << "Enter name: "; getline(cin, name);
                cout << "Enter phone: "; getline(cin, phone);
                cout << "Enter email: "; getline(cin, email);
                cout << "Enter company: "; getline(cin, company);
                cout << "Enter position: "; getline(cin, position);
                contactList.AddContact(new BusinessContact(name, phone, email, company, position));
                break;

            case 3:
                contactList.displayAll();
                break;

            case 4:
                cout << "Enter name to search: "; getline(cin, name);
                contactList.SearchByName(name);
                break;

            case 5:
                cout << "Enter name to delete: "; getline(cin, name);
                if (contactList.DeleteByName(name))
                    cout << "Contact deleted.\n";
                else
                    cout << "Contact not found.\n";
                break;

            case 6:
                cout << "Enter name to edit: "; getline(cin, name);
                if (!contactList.EditContacts(name))
                    cout << "Contact not found.\n";
                break;

            case 7:
                contactList.sortByLastName();
                cout << "Contacts sorted by last name.\n";
                break;

            case 8:
                contactList.saveToFile(filename);
                cout << "Contacts saved to file.\n";
                break;

            case 9:
                contactList.LoadFromFile(filename);
                cout << "Contacts loaded from file.\n";
                break;

            case 0:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}