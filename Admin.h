#ifndef ADMIN_H
#define ADMIN_H
#include "User.h"
#include "Customer.h"
#include <iomanip>

class SuperAdmin;

class Admin : public User
{
private:
    int generateAccountNumber();

public:
    void storeData();
    void login();
    void viewMyInfo();
    void portal();
    int portalMenu();
    bool deleteAccount();	// polymorphism
    void createNewAccount();
    void createCustomerDatabaseBackup();
    void createCustomerDatabaseBackupAnimation();
    void searchCustomer();
    void searchByAccountNumber();
    void searchByName();
    void sortAscending();
    void sortDescending();
    void accountSetting();
    void updateEmail(int);	// polymorphism
    void updateInfo(int);
    void updateContactNumber(int);	// polymorphism
    void changePassword(int);
    void generateReport();
    void viewCustomerAccounts();
};

#endif

