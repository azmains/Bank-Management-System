#include "Transaction.h"
//#include "main.cpp"
#include "UI.h"

int Transaction::generateTransactionID()
{
    std::ifstream fin;
    int num;
    bool isFound = false;
    srand(time(0));
    fin.open("./data/transaction.bank", std::ios::in | std::ios::binary);
    if (!fin)
    {
        std::cout << "File does not exists" << std::endl;
    }
    else
    {
        while (1)
        {
            num = (rand() % 10000) + 100000;
            fin.read((char *)this, sizeof(*this));
            while (fin.eof() == 0)
            {
                if (this->transactionID == num)
                {
                    isFound = true;
                    break;
                }
                fin.read((char *)this, sizeof(*this));
            }
            if (isFound == false)
            {
                break;
            }
        }
    }
    fin.close();
    return num;
}

void Transaction::storeTransaction(int accountNumber, char name[40], unsigned long long int amount, char type[9])
{
    std::ofstream fout;
    fout.open("./data/transaction.bank", std::ios::app | std::ios::binary);
    if (!fout)
    {
        perror("Error");
        Sleep(3000);
        exit(1);
    }
    this->transactionID = generateTransactionID();
    this->accountNumber = accountNumber;
    strcpy(customerName, name);
    this->amount = amount;
    strcpy(transactionType, type);
    fout.write((char *)this, sizeof(*this));
    fout.close();
}

void Transaction::viewTransactionHistoryAdmin()
{
	UI ui;
    ui.TextSize(0, 15);
    std::ifstream fin;
    fin.open("./data/transaction.bank", std::ios::in | std::ios::binary);
    if (!fin)
    {
        perror("Error");
        Sleep(2000);
        exit(1);
    }
    ui.FontColor(4);
    std::cout << "Trx ID                  Name  Acc No      Amount  Transaction Type" << std::endl;
    ui.FontColor(15);
    fin.read((char *)this, sizeof(*this));
    while (fin.eof() == 0)
    {
        std::cout << this->transactionID << "  " << std::setw(20) << this->customerName << "  " << this->accountNumber << "  " << std::setw(10) << this->amount << "  " << this->transactionType << std::endl;
        fin.read((char *)this, sizeof(*this));
    }
    fin.close();
    ui.FontColor(5);
    std::cout << "\nPress any key to continue...";
    ui.CurPosition(0, 0);
    getch();
    ui.TextSize(0, 21);
}

void Transaction::viewTransactionHistoryCustomer(int accNo)
{
	UI ui;
    ui.TextSize(0, 15);
    std::ifstream fin;
    fin.open("./data/transaction.bank", std::ios::in | std::ios::binary);
    if (!fin)
    {
        perror("Error");
        Sleep(2000);
        exit(1);
    }
    std::cout << "Trx ID       Amount             Transaction Type" << std::endl;
    ui.FontColor(7);
    fin.read((char *)this, sizeof(*this));
    while (fin.eof() == 0)
    {
        if (this->accountNumber == accNo)
        {
            std::cout << this->transactionID << "  " << std::setw(20) << std::setw(10) << this->amount << std::setw(25) << this->transactionType << std::endl;
        }
        fin.read((char *)this, sizeof(*this));
    }
    fin.close();
    ui.FontColor(1);
    std::cout << "\nPress any key to continue..." << std::endl;
    getch();
    ui.TextSize(0, 21);
    ui.FontColor(7);
}

int Transaction::getAccountNumber()
{
    return accountNumber;
}

char *Transaction::getName()
{
    return customerName;
}

unsigned long long int Transaction::getAmount()
{
    return amount;
}

char *Transaction::getTransactionType()
{
    return transactionType;
}

int Transaction::getTransactionID()
{
    return transactionID;
}

