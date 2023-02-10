#include "SuperAdmin.h"
#include "UI.h"

void SuperAdmin::manageAdmins()
{
    int choice;
    while (1)
    {
        UI ui;
		ui.FontColor(15);
        system("cls");
        std::cout << "1. View admins" << std::endl;
        std::cout << "2. Add new admin" << std::endl;
        std::cout << "3. Delete admin" << std::endl;
        std::cout << "4. Go Back" << std::endl;
        std::cout << std::endl
             << "Enter your choice: ";
        std::cin >> choice;
        if (choice == 1)
        {
            viewAdmins();
        }
        else if (choice == 2)
        {
            addAdmin();
        }
        else if (choice == 3)
        {
            deleteAdmin();
        }
        else if (choice == 4)
        {
//            SuperAdmin::portal();
break;
        }
        else
        {
            std::cout << "Wrong choice entered, enter a valid choice";
            Sleep(1500);
        }
    }
}

void SuperAdmin::addAdmin()
{
    Admin temp;
    system("cls");
    temp.createNewAccount();
}

void SuperAdmin::viewAdmins()
{
    Admin temp;
    std::ifstream fin;
    fin.open("data/admin.bank", std::ios::in | std::ios::binary);
    if (!fin)
    {
        perror("Error");
        Sleep(2000);
        exit(1);
    }
    fin.read((char *)&temp, sizeof(temp));
    while (fin.eof() == 0)
    {
        std::cout << temp.getAccountNumber() << "      " << std::setw(40) << temp.getName() << "  " << temp.getAge() << "  " << (temp.getGender() == 'm' ? "Male" : "Female") << "  " << temp.getContactNumber() << "  " << temp.getCNIC() << "  " << temp.getEmail() << std::endl;
        fin.read((char *)&temp, sizeof(temp));
    }
    fin.close();
    UI ui;
	ui.FontColor(13);
    std::cout << std::endl
         << "Press any key to continue..." << std::endl;
    getch();
}

void SuperAdmin::deleteAdmin()
{
    bool found = false;
    Admin temp;
    std::ifstream fin;
    std::ofstream fout;
    viewAdmins();
    int accToDelete;
    std::string name1;
    std::cout << "Enter account number to delete: ";
    std::cin >> accToDelete;
    fin.open("data/admin.bank", std::ios::in | std::ios::binary);
    if (!fin)
    {
        perror("Error");
        Sleep(2000);
        exit(1);
    }
    fin.read((char *)&temp, sizeof(temp));
    while (fin.eof() == 0)
    {
        if (accToDelete == temp.getAccountNumber())
        {
            found = true;
            break;
        }
        fin.read((char *)&temp, sizeof(temp));
    }
    fin.close();
    if (found == true)
    {
        fin.open("data/admin.bank", std::ios::in | std::ios::binary);
        fout.open("data/temp.bank", std::ios::out | std::ios::binary);
        if (!fin)
        {
            perror("Error");
            Sleep(2000);
            exit(1);
        }
        fin.read((char *)&temp, sizeof(temp));
        while (fin.eof() == 0)
        {
            if (temp.getAccountNumber() != accToDelete)
            {
                fout.write((char *)&temp, sizeof(temp));
            }
            fin.read((char *)&temp, sizeof(temp));
        }
    }
    else
    {
        std::cout << "This account does not exists" << std::endl;
        Sleep(2000);
    }
    fin.close();
    fout.close();
    if (found == true)
    {
        remove("./data/admin.bank");
        rename("./data/temp.bank", "./data/admin.bank");
        std::cout << "Account deleted successfully" << std::endl;
        Sleep(2500);
    }
    SuperAdmin::portal();
}

void SuperAdmin::viewCurrentRevenue()
{
    Bank bank;
    int count = Bank::calculateTotalAccounts();
    unsigned long long int total = bank.calculateTotalAmount();
    system("cls");
    std::cout << "Total number of accounts: " << count << std::endl;
    std::cout << "Total Amount in bank: USD. " << total << std::endl;
    std::cout << std::endl
         << "Press any key to continue..." << std::endl;
    getch();
}

void SuperAdmin::portal()
{
    system("cls");
    int adminPortalChoice, accNo;
    accNo = this->accountNumber;
    std::ifstream fin;

    while (1)
    {
        adminPortalChoice = SuperAdmin::portalMenu();
        Customer c;
        Transaction t;
        Currency cur;
        switch (adminPortalChoice)
        {
        case 1:
            system("title MY INFO");
            system("color 0B");
            system("cls");
            SuperAdmin::viewMyInfo();
            break;
        case 2:
            system("cls");
            system("title CUSTOMER ACCOUNTS INFO");
            viewCustomerAccounts();
            break;
        case 3:
            system("cls");
            system("title TRANSACTION HISTORY");
            t.viewTransactionHistoryAdmin();
            break;
        case 4:
            system("cls");
            system("title DELETE ACCOUNT");
            Admin::deleteAccount();
            break;
        case 5:
            system("cls");
            system("title ADD NEW CURRENCY");
            cur.addCurrency();
            break;
        case 6:
            system("cls");
            system("title UPDATE CURRENCY RATES");
            cur.updateCurrencyRate();
            break;
        case 7:
            system("cls");
            system("title SEARCH");
            searchCustomer();
            break;
        case 8:
            system("cls");
            system("title CREATING DATABASE BACKUP...");
            createCustomerDatabaseBackup();
            break;
        case 9:
            system("cls");
            system("title MANAGE ADMINS");
            manageAdmins();
            break;
        case 10:
            system("cls");
            viewCurrentRevenue();
            getch();
            break;
        case 11:
        	goto a2;
//            main();
            break;
        default:
            system("cls");
            system("title ERROR");
            UI ui;
			ui.CurPosition(0, 0);
            system("color 4F");
            std::cout << "\aWrong choice entered, try again! \a";
            Sleep(1500);
            system("color 0F");
            break;
        }
    }
    a2:
    	system("cls");
}

int SuperAdmin::portalMenu()
{
    int choice;
    system("color 1F");
    int i;
    system("cls");
    system("title ADMIN PORTAL");
    UI ui;
	ui.CurPosition(0, 0);
    ui.FontColor(15);
    ui.curDateAndTime();
    ui.CurPosition(0, 2);
    ui.FontColor(15);
    std::cout << "Welcome, Mr. Admin(Enter name of super admin here)" << std::endl;
    ui.CurPosition(32, 5);
    ui.FontColor(4);
    std::cout << "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 UNITED BANK LTD \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
    for (i = 1; i <= 22; i++)
    {
        ui.CurPosition(31, 5 + i);
        std::cout << "|";
    }
    for (i = 1; i <= 22; i++)
    {
        ui.CurPosition(91, 5 + i);
        std::cout << "|";
    }
    for (i = 1; i <= 60; i++)
    {
        ui.CurPosition(31 + i, 28);
        std::cout << "-";
    }
    ui.FontColor(15);
    ui.CurPosition(33, 7);
    std::cout << "1. View my information";
    ui.CurPosition(33, 9);
    std::cout << "2. View current accounts information";
    ui.CurPosition(33, 11);
    std::cout << "3. View Transaction History";
    ui.CurPosition(33, 13);
    std::cout << "4. Delete Account";
    ui.CurPosition(33, 15);
    std::cout << "5. Add new currency";
    ui.CurPosition(33, 17);
    std::cout << "6. Update Currency Rates";
    ui.CurPosition(33, 19);
    std::cout << "7. Search and Sort Customers";
    ui.CurPosition(33, 21);
    std::cout << "8. Create Customer Database Backup";
    ui.CurPosition(33, 23);
    std::cout << "9. Manage Admins";
    ui.CurPosition(33, 25);
    std::cout << "10. View Revenue";
    ui.CurPosition(33, 27);
    std::cout << "11. Logout";
    ui.CurPosition(32, 30);
    std::cout << "Enter your choice: ";
    fflush(stdin);
    std::cin >> choice;
    return choice;
}

void SuperAdmin::viewMyInfo()
{
    system("color 0B");
    system("cls");
    system("title MY INFO");
    UI ui;
	ui.FontColor(7);
    std::cout << "Name: ";
    ui.FontColor(2);
    std::cout << "ENTER NAME OF SUPER ADMIN HERE" << std::endl;
    ui.FontColor(7);
    std::cout << "Account No: ";
    ui.FontColor(2);
    std::cout << "12345" << std::endl;
    ui.FontColor(7);
    std::cout << "Age: ";
    ui.FontColor(2);
    std::cout << "18" << std::endl;
    ui.FontColor(7);
    std::cout << "Gender: ";
    ui.FontColor(2);
    std::cout << "Male" << std::endl;
    ui.FontColor(7);
    std::cout << "Contact Number: ";
    ui.FontColor(2);
    std::cout << "03312334567" << std::endl;
    ui.FontColor(7);
    std::cout << "Email: ";
    ui.FontColor(2);
    std::cout << "email@email.com" << std::endl;
    ui.FontColor(7);
    std::cout << "CNIC: ";
    ui.FontColor(2);
    std::cout << "4210101922456" << std::endl
         << std::endl;
    ui.FontColor(1);

    std::cout << "Press any key to go to your portal\n";
    getch();
    system("color 0F");
}

