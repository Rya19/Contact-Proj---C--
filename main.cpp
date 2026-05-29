#include <iostream>
#include <string>
#include "Contact_List.h"
#include "PersonalContact.h"
#include "BusinessContact.h"

using namespace std;

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