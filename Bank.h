#ifndef BANK_H
#define BANK_H
#include <string>

#include <fstream>
class Bank
{
private:
    std::string name;
    static unsigned long long int totalAmountInBank;
    static int totalAccounts;

public:
    Bank() : name("UNITED BANK LTD")
    {
    	totalAmountInBank = 0;
    	totalAccounts = 0;
        totalAmountInBank = calculateTotalAmount();
        totalAccounts = calculateTotalAccounts();
    }
    static unsigned long long int calculateTotalAmount();	// to calculate cuurent amount in bank
    static int calculateTotalAccounts();	// to count total number of existing accounts
    static void incrementAccountCount();	// increment totalAccounts whenever a new account is created
    static void decrementAccountCount();	// decrement totalAccounts whenever an account is deleted
    static void updateData();
    friend class TaxationDepartment;		// TaxationDepartment is friend class of Bank as it needs access to Bank's total amount
};


#endif

