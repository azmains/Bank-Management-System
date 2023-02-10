#include "Bank.h"
#include "Customer.h"
//#include "main.cpp"

unsigned long long int Bank::totalAmountInBank = 0;
int Bank::totalAccounts = 0;

unsigned long long int Bank::calculateTotalAmount()
{
    std::ifstream fin;
    Customer temp;
    unsigned long long int total = 0;
    fin.open("./data/customer.bank", std::ios::in | std::ios::binary);
    if (!fin)
    {
        perror("Error");
        exit(1);
    }
    fin.read((char *)&temp, sizeof(temp));
    while (fin.eof() == 0)
    {
        total += temp.getAmount();
        fin.read((char *)&temp, sizeof(temp));
    }
    fin.close();
    return total;
}

int Bank::calculateTotalAccounts()
{
    int count = 0;
    std::ifstream fin;
    Customer temp;
    fin.open("./data/customer.bank", std::ios::in | std::ios::binary);
    if (!fin)
    {
        perror("Error");
        exit(1);
    }
    fin.read((char *)&temp, sizeof(temp));
    while (fin.eof() == 0)
    {
        count++;
        fin.read((char *)&temp, sizeof(temp));
    }
    fin.close();
    return count;
}

void Bank::incrementAccountCount()
{
    totalAccounts++;
}

void Bank::updateData()
{
    totalAmountInBank = calculateTotalAmount();
    totalAccounts = calculateTotalAccounts();
}

void Bank::decrementAccountCount()
{
    totalAccounts--;
}

