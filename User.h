#ifndef USER_H
#define USER_H
#include <iostream>
#include <conio.h>
#include <fstream>

class User		// Abstract class
{
protected:
    int accountNumber;
    char name[40];
    int age;
    char gender;
    char cnic[14];
    char contactNumber[12];
    char email[30];
    char password[20];
    virtual int generateAccountNumber() = 0;	// pure virtual function
    void inputPassword(char[20]);

public:
    virtual void createNewAccount() = 0;	// pure virtual function
    void setName();		// setter for name
    void setGender();	// setter for gender
    void setCNIC();		// setter for CNIC
    void setContactNumber();	// setter for contact number
    void setEmail();	// setter for email
    void setPassword();		// setter for password
    char *getName();	// getter for name
    int getAccountNumber();		// getter for account number
    char getGender();		// getter for gender
    int getAge();		// getter for age
    char *getCNIC();	// getter for CNIC
    char *getContactNumber();	// getter for contact number
    char *getEmail();		// getter for email
    virtual void storeData() = 0;	// pure virtual function
    void readData();	// to read data from file
    void setAge();	// setter for age
    virtual void login() = 0;	// pure virtual function
    virtual void viewMyInfo() = 0;	// pure virtual function
    virtual void portal() = 0;	// pure virtual function
    virtual int portalMenu() = 0;	// pure virtual function
    virtual bool deleteAccount() = 0;	// pure virtual function
    virtual void accountSetting() = 0;	// pure virtual function
    virtual void updateEmail(int) = 0;	// pure virtual function
    virtual void updateInfo(int) = 0;	// pure virtual function
    virtual void updateContactNumber(int) = 0;	// pure virtual function
    virtual void changePassword(int) = 0;	// pure virtual function
};

#endif

