#include "TaxationDepartment.h"
#include "Bank.h"
double TaxationDepartment::calculateTax()
{
	Bank bank;
    double tax = (double)bank.totalAmountInBank * taxRate;
    return tax;
}

void TaxationDepartment::showInfo()
{
    system("cls");
    Bank bank;
    std::cout << "Bank Name: " << bank.name << std::endl;
    std::cout << "Total number of accounts in bank: " << bank.totalAccounts << std::endl;
    std::cout << "Total amount in bank: USD. " << bank.totalAmountInBank << std::endl;
    std::cout << "Tax Rate: " << taxRate * 100 << " %" << std::endl;
    std::cout << "Tax to be collected from bank: USD. " << calculateTax() << std::endl;
    std::cout << std::endl << "Press any key to continue..." << std::endl;
    getch();
}

