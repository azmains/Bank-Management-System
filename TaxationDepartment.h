#ifndef TAXATIONDEPARTMENT_H
#define TAXATIONDEPARTMENT_H

#include <iostream>
#include <conio.h>

class TaxationDepartment
{
private:
    const float taxRate;
//    Bank bank;

public:
    TaxationDepartment() : taxRate(0.15)	// using member initializer list
    {
    }
    double calculateTax();
    void showInfo();
};

#endif

