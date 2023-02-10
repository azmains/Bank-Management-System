#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include <fstream>

class Customer : public User	// Inheritance
{
private:
    unsigned long long int amount;
    int generateAccountNumber();

public:
    void createNewAccount();
    void depositAmount();
    void withdrawAmount();
    void transferAmount();
    void viewTransactionHistory();
    void login();
    void viewMyInfo();
    void portal();
    int portalMenu();
    void storeData();
    bool deleteAccount();		// polymorphism
    unsigned long long int getAmount();
    void accountSetting();
    void updateEmail(int);		// polymorphism
    void updateInfo(int);
    void updateContactNumber(int);		// polymorphism
    void changePassword(int);
};

#endif

