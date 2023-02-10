#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <iomanip>
class Transaction
{
private:
    int transactionID;
    int accountNumber;
    char customerName[40];
    unsigned long long int amount;
    char transactionType[9];
    int generateTransactionID();

public:
    void storeTransaction(int, char[40], unsigned long long int, char[9]);
    void viewTransactionHistoryAdmin();
    void viewTransactionHistoryCustomer(int);
    char *getName();
    int getAccountNumber();
    unsigned long long int getAmount();
    char *getTransactionType();
    int getTransactionID();
};

#endif

