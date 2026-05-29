#ifndef CONTACT_PERSON_H
#define CONTACT_PERSON_H

#include <string>

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
        Contact_Person(string Contact_Name, string Contact_PhoneNumber, string Contact_Email);

        //Default Constructor
        Contact_Person();

        //Virtual destructor (needed for inheritance)
        virtual ~Contact_Person();
        //Analogy: If someone deletes a contact object, go down to each bit (trail) and delete everything linked to this object
        //With virtual destructors in different contact classes, it'll know which deconstructor to call
        //If a class is meant to be a base (will be inherited from others), and you usep ointers, always make destructor virtual


        //Set/get Functions
        void setContact_Name(string cn);
        string getContact_Name() const; //Const b/c this Member function (function inside a class) won't modify any variables of the class 

        void setContact_PhoneNumber(string cpn);
        string getContact_PhoneNumber() const;
        
        void setContact_Email(string ce);
        string getContact_Email() const;

        //Other functions

        //To display (will be overwritten)
        //Pure virtual because analogy: we want inherited classes to make these functions itself, they must know how to do that, I wont implement that
        //If a derived class (child class) overrides this function, always call the derived version, not THIS version. Ensures correct func gets called at runtime
        //Func must be overriden by any subclass, no base implementation. Can't create objects of this class.
        virtual void display() const = 0;   

        //Format contact info to write to a file
        virtual string toString() const = 0;
};

#endif