#ifndef PERSONAL_CONTACT_H
#define PERSONAL_CONTACT_H

#include "Contact_Person.h"
#include <string>

using namespace std;

class PersonalContact : public Contact_Person {
    private:
        string Contact_Birthday;

    public:
        PersonalContact(string Contact_Name, string Contact_PhoneNumber, string Contact_Email, string Contact_Birthday);

        // Override display()
        void display() const override;

        // Override toString() for saving to a given file
        string toString() const override;

        // Getter and setter for birthday
        string getBirthday() const;
        void setBirthday(string bday);

        // Destructor
        ~PersonalContact();
};

#endif