#include "Admin.h"
#include "SuperAdmin.h"
#include "Transaction.h"
#include "Currency.h"
#include "UI.h"
//#include "main.cpp"

void Admin::storeData()
{
    std::ofstream fout;
    fout.open("./data/admin.bank", std::ios::app | std::ios::binary);
    if (!fout)
    {
        perror("Error");
        Sleep(2500);
        exit(1);
    }
    fout.write((char *)this, sizeof(*this));
    fout.close();
}

void Admin::login()
{
    int id;
    SuperAdmin superAdmin;
    char pass[20];
    bool idFound = false;
    bool passFound = false;
    std::ifstream fin;
    fin.open("./data/admin.bank", std::ios::in | std::ios::binary);
    if (!fin)
    {
        std::cout << "ERROR, file does not exist" << std::endl;
    }
    else
    {
    	UI ui;
        std::cout << "Enter account number: ";
        fflush(stdin);
        ui.FontColor(1);
        std::cin >> id;
        if (id == 12345)
        {
            ui.FontColor(7);
            std::cout << "Enter your password: ";
            inputPassword(pass);
            if (strcmp(pass, "admin") == 0)
            {
                fin.close();
                ui.loadAnimation();
                superAdmin.portal();
            }
        }
        else
        {
            fin.read((char *)this, sizeof(*this));
            while (fin.eof() == 0)
            {
                if (id == this->accountNumber)
                {
                    idFound = true;
                    ui.FontColor(7);
                    std::cout << "Enter your password: ";
                    inputPassword(pass);
                    if (strcmp(password, pass) == 0)
                    {
                        passFound = true;
                        fin.close();
                        ui.loadAnimation();
                        Admin::portal();
                    }
                    else
                    {
                        ui.FontColor(4);
                        std::cout << "\n\t\t\t\t\tWrong password" << std::endl;
                        ui.FontColor(7);
                        Sleep(1000);
                    }
                    break;
                }
                fin.read((char *)this, sizeof(*this));
            }
            if (idFound == false)
            {
                std::cout << "\n\t\t\t\t\t\t";
                ui.FontColor(4);
                std::cout << "This ID does not exists" << std::endl;
                Sleep(1000);
                ui.FontColor(1);
                std::cout << "\nYou are redirected to the mainmenu";
                Sleep(1000);
                ui.loadAnimation();
            }
            fin.close();
        }
    }
}

void Admin::createNewAccount() // this will only be accessed by SuperAdmin
{
    this->accountNumber = generateAccountNumber();
    setName();
    system("cls");
    setGender();
    system("cls");
    setAge();
    system("cls");
    setCNIC();
    system("cls");
    setEmail();
    system("cls");
    setContactNumber();
    system("cls");
    setPassword();
    system("color 0F");
    system("cls");
    UI ui;
	ui.FontColor(15);
    std::cout << "Account Number  : ";
    ui.FontColor(9);
    std::cout << this->accountNumber << std::endl;
    ui.FontColor(15);
    std::cout << "Name            : ";
    ui.FontColor(10);
    std::cout << this->name << std::endl;
    ui.FontColor(15);
    std::cout << "Age             : ";
    ui.FontColor(10);
    std::cout << this->age << std::endl;
    ui.FontColor(15);
    std::cout << "Contact Number  : ";
    ui.FontColor(10);
    std::cout << this->contactNumber << std::endl;
    ui.FontColor(15);
    std::cout << "CNIC: ";
    ui.FontColor(10);
    std::cout << this->cnic << std::endl;
    ui.FontColor(15);
    std::cout << "Email: ";
    ui.FontColor(10);
    std::cout << this->email << std::endl;
    std::cout << "\nAre your sure you want to create your account: [y/n]: ";
    char ch, choice;
    while (1)
    {
        ch = getch();
        if (ch == 'y' || ch == 'Y' || ch == 'n' || ch == 'N')
        {
            choice = ch;
            std::cout << ch << std::endl;
            break;
        }
    }
    system("color 0F");
    if (choice == 'y' || choice == 'Y')
    {
        Admin::storeData();
        std::cout << "Account created successfully\n";
        Sleep(1000);
    }
}

void Admin::portal()
{
    system("cls");
    int adminPortalChoice, accNo;
    accNo = this->accountNumber;
    std::ifstream fin;

    while (1)
    {
        fin.open("./data/admin.bank", std::ios::in | std::ios::binary);
        if (!fin)
        {
            system("cls");
            perror("Error");
            std::cout << "\nProgram will exit\n";
            Sleep(2000);
            exit(1);
        }
        fin.read((char *)this, sizeof(*this));
        while (fin.eof() == 0)
        {
            if (accNo == accountNumber)
            {
                break;
            }
            fin.read((char *)this, sizeof(*this));
        }
        fin.close();
        adminPortalChoice = Admin::portalMenu();
        Customer c;
        Transaction t;
        Currency cur;
        switch (adminPortalChoice)
        {
        case 1:
            system("title MY INFO");
            system("color 0B");
            system("cls");
            Admin::viewMyInfo();
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
            system("title ACCOUNT SETTING");
            Admin::accountSetting();
            break;
        case 10:
//            main();
            goto a1;
            break;
        case 11:
            generateReport();
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
    a1:
    	system("cls");
}

int Admin::portalMenu()
{
    int choice;
    system("color 0F");
    int i;
    system("cls");
    system("title ADMIN PORTAL");
    UI ui;
	ui.CurPosition(0, 0);
    ui.FontColor(10);
    ui.curDateAndTime();
    ui.CurPosition(0, 2);
    ui.FontColor(9);
    std::cout << "Welcome, " << this->name << std::endl;
    ui.CurPosition(32, 5);
    ui.FontColor(3);
    std::cout << "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 UNITED BANK LTD \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
    for (i = 1; i <= 21; i++)
    {
        ui.CurPosition(31, 5 + i);
        std::cout << "|";
    }
    for (i = 1; i <= 21; i++)
    {
        ui.CurPosition(91, 5 + i);
        std::cout << "|";
    }
    for (i = 1; i <= 60; i++)
    {
        ui.CurPosition(31 + i, 27);
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
    std::cout << "9. Account Settings";
    ui.CurPosition(33, 25);
    std::cout << "10. Logout";
    ui.CurPosition(32, 28);
    std::cout << "Enter your choice: ";
    fflush(stdin);
    std::cin >> choice;
    return choice;
}

void Admin::viewMyInfo()
{
    system("color 0B");
    system("cls");
    system("title MY INFO");
    UI ui;
	ui.FontColor(7);
    std::cout << "Name: ";
    ui.FontColor(2);
    std::cout << this->name << std::endl;
    ui.FontColor(7);
    std::cout << "Account No: ";
    ui.FontColor(2);
    std::cout << this->accountNumber << std::endl;
    ui.FontColor(7);
    std::cout << "Age: ";
    ui.FontColor(2);
    std::cout << this->age << std::endl;
    ui.FontColor(7);
    std::cout << "Gender: ";
    ui.FontColor(2);
    std::cout << (this->gender == 'm' ? "Male" : "Female") << std::endl;
    ui.FontColor(7);
    std::cout << "Contact Number: ";
    ui.FontColor(2);
    std::cout << this->contactNumber << std::endl;
    ui.FontColor(7);
    std::cout << "Email: ";
    ui.FontColor(2);
    std::cout << this->email << std::endl;
    ui.FontColor(7);
    std::cout << "CNIC: ";
    ui.FontColor(2);
    std::cout << this->cnic << std::endl
         << std::endl;
    ui.FontColor(1);

    std::cout << "Press any key to go to your portal\n";
    getch();
    system("color 0F");
}

void Admin::viewCustomerAccounts()
{
    UI ui;
	ui.TextSize(0, 14);
    std::ifstream fin;
    Customer c;
    fin.open("./data/customer.bank", std::ios::in | std::ios::binary);
    if (!fin)
    {
        perror("Error");
        exit(1);
    }
    fin.read((char *)&c, sizeof(c));
    ui.FontColor(4);
    std::cout << "Account No  " << std::setw(28) << "  Name  " << std::setw(7) << "Age" << std::setw(3) << " Gender "
         << "Phone#       "
         << " CNIC#" << std::setw(31) << "email" << std::setw(17) << "balance"
         << "\n\n";
    ui.FontColor(15);
    while (fin.eof() == 0)
    {
        std::cout << c.getAccountNumber() << "      " << std::setw(30) << c.getName() << "  " << c.getAge() << "   " << (c.getGender() == 'm' ? "Male" : "Female") << "  " << c.getContactNumber() << "  " << c.getCNIC() << "  " << std::setw(30) << c.getEmail() << "  " << c.getAmount() << "\n"
             << std::endl;
        fin.read((char *)&c, sizeof(c));
    }
    fin.close();
    ui.FontColor(13);
    std::cout << "Press any key to continue..." << std::endl;
    getch();
    ui.TextSize(0, 21);
}

bool Admin::deleteAccount()
{
    int accountToDelete;
    char ch, choice;
    std::ofstream fout;
    Customer c;
    bool accountFound = false;
    std::cout << "Enter account number to delete: ";
    fflush(stdin);
    std::cin >> accountToDelete;
    std::ifstream fin;
    fin.open("./data/customer.bank", std::ios::in | std::ios::binary);
    if (!fin)
    {
        perror("Error");
        Sleep(2000);
        exit(1);
    }
    fin.read((char *)&c, sizeof(c));
    while (fin.eof() == 0)
    {
        if (accountToDelete == c.getAccountNumber())
        {
            c.viewMyInfo();
            accountFound = true;
            break;
        }
        fin.read((char *)&c, sizeof(c));
    }
    fin.close();

    if (accountFound == true)
    {
        UI ui;
		ui.FontColor(4);
        std::cout << "\n\t\t\t\t\tAre you sure you want to delete this account? [y/n]: ";
        ui.FontColor(7);
        while (1)
        {
            ch = getch();
            if (ch == 'y' || ch == 'Y' || ch == 'n' || ch == 'N')
            {
                std::cout << ch;
                choice = ch;
                break;
            }
        }
        if (choice == 'y' || choice == 'Y')
        {
            fout.open("./data/temp.bank", std::ios::out | std::ios::binary);
            fin.open("./data/customer.bank", std::ios::in | std::ios::binary);
            if (!fin)
            {
                perror("Error");
                Sleep(2000);
                exit(1);
            }
            else
            {
                fin.read((char *)&c, sizeof(c));
                while (fin.eof() == 0)
                {
                    if (c.getAccountNumber() != accountToDelete)
                    {
                        fout.write((char *)&c, sizeof(c));
                    }
                    fin.read((char *)&c, sizeof(c));
                }
            }
            fin.close();
            fout.close();
            if (accountFound == true)
            {
                remove("./data/customer.bank");
                rename("./data/temp.bank", "./data/customer.bank");
                ui.FontColor(2);
                std::cout << "\n\t\t\t\t\tAccount deleted successfully" << std::endl;
                Bank::decrementAccountCount();
                ui.FontColor(7);
                Sleep(2000);
            }
        }
    }
    else
    {
        UI ui;
		ui.FontColor(4);
        std::cout << "\n\t\t\t\t\tThis account does not exists" << std::endl;
        ui.FontColor(7);
        Sleep(2000);
    }
}

void Admin::createCustomerDatabaseBackup()		// data backup
{
    std::string fileName;
    Customer c;
    std::ifstream fin;
    
    fileName = "./data/backup/";
    char fname[16];
    char date[50];
    time_t t;
    time(&t);
    strcpy(date, ctime(&t));
    fileName += date[0];
    fileName += date[1];
    fileName += date[2];
    fileName += " ";
    fileName += date[4];
    fileName += date[5];
    fileName += date[6];
    fileName += " ";
    fileName += date[8];
    fileName += date[9];
    fileName += " ";
    fileName += date[20];
    fileName += date[21];
    fileName += date[22];
    fileName += date[23];
    fileName += ".bank";
    fin.open("./data/customer.bank", std::ios::in | std::ios::binary);
    std::ofstream fout(fileName.c_str());
//    fout.open(fileName, ios::out | ios::binary);
    fin.read((char *)&c, sizeof(c));
    while (fin.eof() == 0)
    {
        fout.write((char *)&c, sizeof(c));
        fin.read((char *)&c, sizeof(c));
    }
    fin.close();
    fout.close();
    createCustomerDatabaseBackupAnimation();
}

void Admin::createCustomerDatabaseBackupAnimation()
{
    int i;
    system("cls");
    system("color 09");
    UI ui;
	ui.CurPosition(50, 10);
    printf("Creating Backup");
    ui.CurPosition(40, 12);
    printf("[");
    ui.CurPosition(78, 12);
    printf("]");
    ui.CurPosition(41, 12);
    for (i = 1; i <= 37; i++)
    {
        printf("%c", 177);
    }
    ui.CurPosition(41, 12);
    for (i = 1; i <= 37; i++)
    {
        Sleep(35);
        printf("%c", 219);
    }
    ui.CurPosition(0, 0);
    system("cls");
    system("color 0A");
    printf("Backup Created Successfully");
    Sleep(2000);
    system("cls");
}

int Admin::generateAccountNumber()
{
    std::ifstream fin;
    int num;
    bool isFound = false;
    srand(time(0));
    fin.open("./data/admin.bank", std::ios::in | std::ios::binary);
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
                if (this->accountNumber == num)
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

void Admin::searchCustomer()
{
    int choice;
    std::cout << "1. Search by Account Number" << std::endl;
    std::cout << "2. Search by Name" << std::endl;
    std::cout << "3. Sort by amount (ASCENDING)" << std::endl;
    std::cout << "4. Sort by amount (DESCENDING)" << std::endl;
    std::cout << "5. Go back" << std::endl
         << std::endl;
    ;
    UI ui;
	ui.FontColor(10);
    std::cout << "Enter your choice: ";
    fflush(stdin);
    ui.FontColor(15);
    std::cin >> choice;

    system("cls");
    switch (choice)
    {
    case 1:
        searchByAccountNumber();
        break;
    case 2:
        searchByName();
        break;
    case 3:
        sortAscending();
        break;
    case 4:
        sortDescending();
        break;
    case 5:
        break;
    default:
        std::cout << "Wrong choice entered, please enter a correct choice" << std::endl;
        Sleep(1500);
        break;
    }
}

void Admin::searchByAccountNumber()
{
    int accountNumberToSearch;
    std::ifstream fin;
    bool accountFound = false;
    Customer c;
    system("cls");
    while (1)
    {
        std::cout << "Enter account number to search: ";
        fflush(stdin);
        std::cin >> accountNumberToSearch;
        fin.open("./data/customer.bank", std::ios::in | std::ios::binary);
        fin.read((char *)&c, sizeof(c));
        while (fin.eof() == 0)
        {
            if (accountNumberToSearch == c.getAccountNumber())
            {
                accountFound = true;
                c.viewMyInfo();
                goto searchByAccountNumberEnd;
            }
            fin.read((char *)&c, sizeof(c));
        }
        if (accountFound == false)
        {
            system("cls");
            UI ui;
			ui.FontColor(4);
            std::cout << "\n\t\t\t\t\tThis account does not exists" << std::endl;
            Sleep(2000);
            ui.FontColor(7);
            goto searchByAccountNumberEnd;
        }
    }
searchByAccountNumberEnd:
    fin.close();
}

void Admin::searchByName()
{
    char name[40];
    bool found = false;
    int total = 0;
    std::ifstream fin;
    Customer c;
    system("cls");
    UI ui;
	ui.FontColor(2);
    fflush(stdin);
    gets(name);
    system("cls");
    ui.FontColor(7);
    fin.open("./data/customer.bank", std::ios::in | std::ios::binary);
    fin.read((char *)&c, sizeof(c));
    while (1)
    {
        while (fin.eof() == 0)
        {
            if (strcmp(name, c.getName()) == 0)
            {
                found = true;
                system("title SEARCH");
                ui.FontColor(7);
                std::cout << "Name: ";
                ui.FontColor(2);
                std::cout << c.getName() << std::endl;
                ui.FontColor(7);
                std::cout << "Account No: ";
                ui.FontColor(2);
                std::cout << c.getAccountNumber() << std::endl;
                ui.FontColor(7);
                std::cout << "Age: ";
                ui.FontColor(2);
                std::cout << c.getAge() << std::endl;
                ui.FontColor(7);
                std::cout << "Gender: ";
                ui.FontColor(2);
                std::cout << (c.getGender() == 'm' ? "Male" : "Female") << std::endl;
                ui.FontColor(7);
                std::cout << "Contact Number: ";
                ui.FontColor(2);
                std::cout << c.getContactNumber() << std::endl;
                ui.FontColor(7);
                std::cout << "Email: ";
                ui.FontColor(2);
                std::cout << c.getEmail() << std::endl;
                std::cout << "CNIC: ";
                ui.FontColor(2);
                std::cout << c.getCNIC() << std::endl
                     << std::endl;
                total++;
                std::cout << std::endl;
            }
            fin.read((char *)&c, sizeof(c));
        }
        if (found == true)
        {
            ui.FontColor(1);
            std::cout << "There are currently " << total << " account(s) with this name" << std::endl;
            ui.FontColor(7);
            std::cout << "\nPress any key to continue..." << std::endl;
            getch();
            break;
        }
        else
        {
            ui.FontColor(4);
            std::cout << "\n\t\t\t\t\tThere are no account with this name" << std::endl;
            Sleep(2000);
            ui.FontColor(7);
            break;
        }
    }
searchByNameEnd:
    fin.close();
}

void Admin::sortAscending()
{
    int size, i, j;
    UI ui;
	ui.TextSize(0, 18);
    size = 0;
    Customer *cust;
    Customer c, temp;
    std::ifstream fin;
    fin.open("./data/customer.bank", std::ios::in | std::ios::binary);
    fin.read((char *)&c, sizeof(c));
    while (fin.eof() == 0)
    {
        size++;
        fin.read((char *)&c, sizeof(c));
    }
    fin.close();
    if (size != 0)
    {
        cust = new Customer[size];
        i = 0;
        fin.open("./data/customer.bank", std::ios::in | std::ios::binary);
        fin.read((char *)&c, sizeof(c));
        while (fin.eof() == 0)
        {
            *(cust + i) = c;
            i++;
            fin.read((char *)&c, sizeof(c));
        }
        fin.close();
        for (i = 1; i < size; i++)
        {
            for (j = 0; j < size - i; j++)
            {
                if (cust[j].getAmount() > cust[j + 1].getAmount())
                {
                    temp = cust[j];
                    cust[j] = cust[j + 1];
                    cust[j + 1] = temp;
                }
            }
        }
        for (i = 0; i < size; i++)
        {
            std::cout << cust[i].getAccountNumber() << "      " << std::setw(40) << cust[i].getName() << "  " << cust[i].getAge() << "  " << (cust[i].getGender() == 'm' ? "Male" : "Female") << "  " << cust[i].getContactNumber() << "  " << cust[i].getCNIC() << "  " << cust[i].getEmail() << "  " << cust[i].getAmount() << std::endl;
        }
        std::cout << "\nPress any to continue..." << std::endl;
        getch();
    }
    else
    {
        std::cout << "Empty" << std::endl;
    }
    delete[] cust;
    cust = NULL;
}

void Admin::sortDescending()
{
    int size, i, j;
    size = 0;
    Customer *cust;
    Customer c, temp;
    std::ifstream fin;
    fin.open("./data/customer.bank", std::ios::in | std::ios::binary);
    fin.read((char *)&c, sizeof(c));
    while (fin.eof() == 0)
    {
        size++;
        fin.read((char *)&c, sizeof(c));
    }
    fin.close();
    if (size != 0)
    {
        cust = new Customer[size];
        i = 0;
        fin.open("./data/customer.bank", std::ios::in | std::ios::binary);
        fin.read((char *)&c, sizeof(c));
        while (fin.eof() == 0)
        {
            *(cust + i) = c;
            i++;
            fin.read((char *)&c, sizeof(c));
        }
        fin.close();
        for (i = 1; i < size; i++)
        {
            for (j = 0; j < size - i; j++)
            {
                if (cust[j].getAmount() < cust[j + 1].getAmount())
                {
                    temp = cust[j];
                    cust[j] = cust[j + 1];
                    cust[j + 1] = temp;
                }
            }
        }
        for (i = 0; i < size; i++)
        {
            std::cout << cust[i].getAccountNumber() << "      " << std::setw(40) << cust[i].getName() << "  " << cust[i].getAge() << "  " << (cust[i].getGender() == 'm' ? "Male" : "Female") << "  " << cust[i].getContactNumber() << "  " << cust[i].getCNIC() << "  " << cust[i].getEmail() << "  " << cust[i].getAmount() << std::endl;
        }
        std::cout << "\nPress any to continue..." << std::endl;
        getch();
    }
    else
    {
        std::cout << "Empty" << std::endl;
    }
    delete[] cust;
    cust = NULL;
}

void Admin::accountSetting()
{
    int choice;
    while (1)
    {
        system("cls");
        std::cout << "1. Update my email" << std::endl;
        std::cout << "2. Update my contact number" << std::endl;
        std::cout << "3. Change my password" << std::endl;
        std::cout << "4. Go back" << std::endl;
        UI ui;
		ui.FontColor(1);
        std::cout << std::endl
             << "Enter your choice: ";
        ui.FontColor(7);
        fflush(stdin);
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            Admin::updateEmail(this->accountNumber);
            break;
        case 2:
            Admin::updateContactNumber(this->accountNumber);
            break;
        case 3:
            Admin::changePassword(this->accountNumber);
            break;
        case 4:
            goto adminAccountSettingEnd;
            break;
        default:
            ui.FontColor(4);
            std::cout << "Enter a valid choice" << std::endl;
            Sleep(1000);
            ui.FontColor(7);
            break;
        }
    }
adminAccountSettingEnd:
    system("cls");
}

void Admin::updateInfo(int accNo)
{
    std::fstream file;
    Admin a;
    file.open("./data/admin.bank", std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
    file.seekg(0);
    file.read((char *)&a, sizeof(a));
    while (file.eof() == 0)
    {
        if (a.accountNumber == accNo)
        {
            file.seekp(file.tellp() - sizeof(a));
            file.write((char *)this, sizeof(*this));
            break;
        }
        file.read((char *)&a, sizeof(a));
    }
    file.close();
}

void Admin::updateEmail(int accNo)
{
    setEmail();
    system("cls");
    std::cout << "Enter your password to confirm: ";
    char passToConfirm[20];
    inputPassword(passToConfirm);
    if (strcmp(password, passToConfirm) == 0)
    {
        Admin::updateInfo(accNo);
    }
}

void Admin::updateContactNumber(int accNo)
{
    setContactNumber();
    system("cls");
    std::cout << "Enter your password to confirm: ";
    char passToConfirm[20];
    inputPassword(passToConfirm);
    if (strcmp(password, passToConfirm) == 0)
    {
        Admin::updateInfo(accNo);
    }
}

void Admin::changePassword(int accNo)
{
    char passToConfirm[20];
    std::cout << "Enter your password to confirm: ";
    inputPassword(passToConfirm);
    if (strcmp(password, passToConfirm) == 0)
    {
        system("cls");
        system("title ENTER NEW PASSWORD");
        setPassword();
        Admin::updateInfo(accNo);
    }
}

void Admin::generateReport()
{
    std::ifstream fin;
    std::ofstream fout;
    Transaction t;
    fin.open("./data/transaction.bank", std::ios::in | std::ios::binary);
    fout.open("a.csv", std::ios::out);
    fout << "Name,Account_Number,Amount,Type" << std::endl;
    fin.read((char *)&t, sizeof(t));
    while (fin.eof() == 0)
    {
        fout << t.getName() << "," << t.getAccountNumber() << "," << t.getAmount() << "," << t.getTransactionType() << std::endl;
        fin.read((char *)&t, sizeof(t));
    }
    fin.close();
    fout.close();
}

