#include "Contact_Person.h"

Contact_Person::Contact_Person(string Contact_Name, string Contact_PhoneNumber, string Contact_Email) {
    this->Contact_Name = Contact_Name;
    this->Contact_PhoneNumber = Contact_PhoneNumber;
    this->Contact_Email = Contact_Email;

    /*
    Can also use:

    Contact_Person(parameters) :
    parameter1(parameter1), parameter2(parameter2), ...
    
    */
}

Contact_Person::Contact_Person() {
    Contact_Name = "";
    Contact_PhoneNumber = "";
    Contact_Email = "";
}

Contact_Person::~Contact_Person() {
    //nothing here yet
}

void Contact_Person::setContact_Name(string cn) {
    this->Contact_Name = cn;
}

string Contact_Person::getContact_Name() const { 
    return Contact_Name;
}

void Contact_Person::setContact_PhoneNumber(string cpn) {
    this->Contact_PhoneNumber = cpn;
}

string Contact_Person::getContact_PhoneNumber() const {
    return Contact_PhoneNumber;
}

void Contact_Person::setContact_Email(string ce) {
    this->Contact_Email = ce; //can just do Contact_Email = ce
}

string Contact_Person::getContact_Email() const {
    return Contact_Email;
}