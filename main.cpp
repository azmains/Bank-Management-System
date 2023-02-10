#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <fstream>
#include <windows.h>
#include <ctype.h>
#include <iomanip>
#include <cwchar>
#include "Customer.h"
#include "Admin.h"
#include "Currency.h"
#include "TaxationDepartment.h"
#include "Bank.h"
#include "UI.h"
UI ui;
int main() {
    // system("mode 134, 32");
    int MainMenuChoice;
    Customer c;
    Admin a;
    Currency *cur = new Currency;	// using DMA (new keyword)
    TaxationDepartment *taxationDep = new TaxationDepartment;		// new
    while (1)
    {
    	// main menu of the program
        system("cls");
        Bank::updateData();		// using scope resolution operator
        MainMenuChoice = ui.MainMenu();
        switch (MainMenuChoice)
        {
        case 1:
            system("cls");
            system("title Admin Login");
            a.login();
            break;
        case 2:
            system("cls");
            system("title Customer Login");
            c.login();
            break;
        case 3:
            system("cls");
            system("title Create New Account");
            c.createNewAccount();
            break;
        case 4:
            system("cls");
            system("title Today's Currency Rates");
            cur->viewCurrencyRates();		// using arrow operator
            break;
        case 5:
            system("cls");
            system("title About Us");
            ui.AboutUs();
            break;
        case 6:
            system("cls");
            taxationDep->showInfo();
            break;
        case 7:
            system("cls");
            ui.CurPosition(40, 10);
            system("title Good Bye");
            ui.Box();
            Sleep(2000);
            ui.FontColor(7);
            delete cur;		// using delete to deallocate resource
            delete taxationDep;	// delete
            exit(0);
            break;
        default:
            system("cls");
            system("title ERROR :(");
            ui.CurPosition(0, 0);
            system("color 4F");
            std::cout << "Wrong choice entered, try again!";
            Beep(1000, 300);
            Sleep(2000);
            system("color 0F");
            break;
        }
    }
	return 0;
}



