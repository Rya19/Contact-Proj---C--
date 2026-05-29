#include "BusinessContact.h"
#include <iostream>

BusinessContact::BusinessContact(string Contact_Name, string Contact_PhoneNumber, string Contact_Email, string Contact_CompanyName, string Contact_JobTitle) : Contact_Person(Contact_Name, Contact_PhoneNumber, Contact_Email) // Call base class constructor
{
    this->Contact_CompanyName = Contact_CompanyName;
    this->Contact_JobTitle = Contact_JobTitle;
}

void BusinessContact::display() const {
    cout << "Business Contact:" << endl;
    cout << "Name: " << Contact_Name << endl;
    cout << "Phone: " << Contact_PhoneNumber << endl;
    cout << "Email: " << Contact_Email << endl;
    cout << "Company: " << Contact_CompanyName << endl;
    cout << "Job Title: " << Contact_JobTitle << endl;
}

string BusinessContact::toString() const {
    return "B-C," + Contact_Name + "," + Contact_PhoneNumber + "," + Contact_Email + "," + Contact_CompanyName + "," + Contact_JobTitle;
}

string BusinessContact::getContact_CompanyName() const { 
    return Contact_CompanyName; 
}

void BusinessContact::setContact_CompanyName(string company) { 
    Contact_CompanyName = company; 
}

string BusinessContact::getContact_JobTitle() const { 
    return Contact_JobTitle; 
}

void BusinessContact::setContact_JobTitle(string title) { 
    Contact_JobTitle = title; 
}

BusinessContact::~BusinessContact() {
    
}