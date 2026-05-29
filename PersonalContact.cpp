#include "PersonalContact.h"
#include <iostream>

PersonalContact::PersonalContact(string Contact_Name, string Contact_PhoneNumber, string Contact_Email, string Contact_Birthday) : Contact_Person(Contact_Name, Contact_PhoneNumber, Contact_Email) {
    this->Contact_Birthday = Contact_Birthday;
}

void PersonalContact::display() const {
    cout << "Personal Contact:" << endl;
    cout << "Name: " << Contact_Name << endl;
    cout << "Phone: " << Contact_PhoneNumber << endl;
    cout << "Email: " << Contact_Email << endl;
    cout << "Birthday: " << Contact_Birthday << endl;
}

string PersonalContact::toString() const {
    return "P-C," + Contact_Name + "," + Contact_PhoneNumber + "," + Contact_Email + "," + Contact_Birthday;
}

string PersonalContact::getBirthday() const { 
    return Contact_Birthday; 
}

void PersonalContact::setBirthday(string bday) { 
    Contact_Birthday = bday; 
}

PersonalContact::~PersonalContact() {
    
}