#ifndef CURRENCY_H
#define CURRENCY_H
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <iomanip>

class Currency
{
private:
    int code;
    char name[25];
    char symbol[4];
    float rate;
    int generateCurrencyCode();

public:
    void addCurrency();
    void updateCurrencyRate();
    void viewCurrencyRates() const;
    void setRate(float);
    void addCurrency(int, char[25], char[4], float);
    friend std::ostream &operator<<(std::ostream &, const Currency &);
};

#endif

