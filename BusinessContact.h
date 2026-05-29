#ifndef BUSINESS_CONTACT_H
#define BUSINESS_CONTACT_H

#include "Contact_Person.h"
#include <string>

using namespace std;

class BusinessContact : public Contact_Person {
private:
    string Contact_CompanyName;
    string Contact_JobTitle;

public:
    // Constructor
    BusinessContact(string Contact_Name, string Contact_PhoneNumber, string Contact_Email, string Contact_CompanyName, string Contact_JobTitle);

    // Override display() as usual
    void display() const override;

    // Override toString() for saving to a given file as usual
    string toString() const override;

    // Getters and Setters
    string getContact_CompanyName() const;
    void setContact_CompanyName(string company);

    string getContact_JobTitle() const;
    void setContact_JobTitle(string title);

    // Destructor
    ~BusinessContact();
};

#endif