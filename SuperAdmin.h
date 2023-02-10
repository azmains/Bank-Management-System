#ifndef SUPERADMIN_H
#define SUPERADMIN_H

#include "Admin.h"
#include <iomanip>
#include "Bank.h"
#include "Transaction.h"
#include "Currency.h"
//#include "main.cpp"
class SuperAdmin : public Admin		// Inheritance
{
public:
    void addAdmin();
    void deleteAdmin();
    void portal();
    int portalMenu();
    void viewCurrentRevenue();
    void viewAdmins();
    void manageAdmins();
    void viewMyInfo();		// polymorphism
};

#endif

