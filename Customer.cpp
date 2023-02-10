#include "Customer.h"
#include "Bank.h"
#include "Transaction.h"
#include "UI.h"
//#include "main.cpp"

void bankPolicy()
{
	UI ui;
    system("cls");
    system("title Bank Policy");
    system("color F0");
    ui.FontColor(0);
    printf("By signing, you, the individual(s) named in this form are:\n\n");
    ui.FontColor(1);
    printf("1. Confirming you are applying to the Bank for banking services;\n");
    printf("2. Confirming that any details you have supplied to us are true and complete;\n");
    printf("3. Authorizing us to:\n");
    printf("        i.  Make credit reference and other inquiries in connection with this application in accordance with our\n");
    printf("            normal procedures; and\n");
    printf("        ii. Disclose information to licensed credit reference agencies and otherwise in accordance with\n");
    printf("            conditions 94-105 of General Terms and Conditions.\n");
    printf("4. Confirming that you understand that credit reference agencies record information and the information they\n");
    printf("   record may be used by other organizations to help make decisions about credit and credit-related services and\n");
    printf("   to manage accounts for customers and for fraud prevention.\n");
    printf("5. Agreeing to be bound by the terms of the application and the Bank's General Terms and Conditions which contain\n");
    printf("   your obligations to us and our obligations to you which may be altered from time to time;\n");
    printf("6. Understanding that the Bank may decline your account without stating a reason.\n");
    printf("7. Contact the admin directly in case of any issues\n");
    printf("\nPress any key to continue...");
    getch();
    system("cls");
    system("color F4");
    ui.FontColor(4);
    printf("Before proceeding further:\n");
    ui.FontColor(0);
    printf("1.	Make sure to record your account number\n");
    printf("2.	In case you forgot your account number, contact the admin, and provide your full information for authentication\n");
    printf("3.	Make sure to log out of your account after use.\n");
    printf("4.	Make sure to read the user guide before using Banking System\n\n");

    ui.FontColor(4);
    printf("The Bank will not be responsible if:\n");
    ui.FontColor(0);
    printf("1.	User forgets to log out of his/her account\n");
    printf("2.	User edits, modifies or deletes the database files\n\n");
    ui.FontColor(2);
    printf("Press any key to continue...");
    getch();
    system("cls");
    system("color 0F");
}

void Customer::createNewAccount()
{
	UI ui;
    bankPolicy();
    char mailContent[256];
    char accNo[7];
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
    this->amount = 0;
    system("color 0F");
    system("cls");
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
    std::cout << "Account Balance : ";
    ui.FontColor(10);
    std::cout << "Rs. " << this->amount << std::endl
         << std::endl;
    ui.FontColor(1);
    std::cout << "\nAre your sure you want to create your account: [y/n]: ";
    std::sprintf(accNo, "%llu", accountNumber);
    accNo[6] = '\0';
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
    std::cout << std::endl;
    system("color 0F");
    if (choice == 'y' || choice == 'Y')
    {
        Customer::storeData();
        std::cout << "Account created successfully\n";
        Bank::incrementAccountCount();
        ui.FontColor(1);
        std::cout << "\nYou are redirected to the mainmenu\n";
        ui.FontColor(0);
        ui.loadAnimation();
    }
}

int Customer::generateAccountNumber()
{
    std::ifstream fin;
    int num;
    bool isFound = false;
    srand(time(0));
    fin.open("./data/customer.bank", std::ios::in | std::ios::binary);
    if (!fin)
    {
        perror("Error");
        Sleep(2000);
        exit(1);
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



void Customer::storeData()
{
    std::ofstream fout;
    fout.open("./data/customer.bank", std::ios::app | std::ios::binary);
    if (!fout)
    {
        perror("Error");
        Sleep(2000);
        exit(1);
    }
    fout.write((char *)this, sizeof(*this));
    fout.close();
}

unsigned long long int Customer::getAmount()
{
    return amount;
}

void Customer::login()
{
    int id;
    char pass[20];
    bool idFound = false;
    bool passFound = false;
    std::ifstream fin;
    fin.open("./data/customer.bank", std::ios::in | std::ios::binary);
    if (!fin)
    {
        std::cout << "ERROR, file does not exist" << std::endl;
    }
    else
    {
    	UI ui;
        std::cout << "Enter account number: ";
        ui.FontColor(1);
        fflush(stdin);
        std::cin >> id;
        ui.FontColor(7);
        fin.read((char *)this, sizeof(*this));
        while (fin.eof() == 0)
        {
            if (id == this->accountNumber)
            {
                idFound = true;
                std::cout << "Enter your password: ";
                inputPassword(pass);
                if (strcmp(password, pass) == 0)
                {
                    passFound = true;
                    fin.close();
                    ui.loadAnimation();
                    Customer::portal();
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
            std::cout << "You are redirected to the main menu...";
            Sleep(1000);
            ui.loadAnimation();
        }
        fin.close();
    }
}

void Customer::viewMyInfo()
{
    UI ui;
	system("color 0B");
    system("cls");
    system("title MY INFO");
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
    ui.FontColor(7);
    std::cout << "Current Balance: ";
    ui.FontColor(2);
    std::cout << this->amount << std::endl;
    ui.FontColor(1);

    std::cout << "\n\t\t\t\t\tPress any key to go to your portal\n";
    getch();
    system("color 0F");
}

void Customer::portal()
{
    system("cls");
    int customerPortalChoice, accNo;
    accNo = accountNumber;
    std::ifstream fin;
    Transaction t;

    while (1)
    {
        fin.open("./data/customer.bank", std::ios::in | std::ios::binary);
        if (!fin)
        {
            system("cls");
            perror("Error");
            std::cout << "\nProgram will exit\n";
            Sleep(2000);
            exit(1);
        }
        fin.read((char *)this, sizeof(*this));
        bool found = false;
        while (fin.eof() == 0)
        {
            if (accNo == accountNumber)
            {
            	found = true;
                break;
            }
            fin.read((char *)this, sizeof(*this));
        }
        fin.close();
        if(found == false){
        	goto customerPortalEnd;
		}
        customerPortalChoice = Customer::portalMenu();
        switch (customerPortalChoice)
        {
        case 1:
            Customer::viewMyInfo();
            // customerPortal();
            break;
        case 2:
            system("cls");
            system("title DEPOSIT AMOUNT");
            depositAmount();
            break;
        case 3:
            system("cls");
            system("title WITHDRAW AMOUNT");
            withdrawAmount();
            break;
        case 4:
            system("cls");
            system("title TRANSFER AMOUNT");
            transferAmount();
            break;
        case 5:
            system("cls");
            system("title VIEW TRANSACTION HISTORY");
            t.viewTransactionHistoryCustomer(accNo);
            break;
        case 6:
            system("cls");
            system("title DELETE ACCOUNT");
            Customer::accountSetting();
            break;
        case 7:
            goto customerPortalEnd;
            break;
        default:
            UI ui;
			system("cls");
            system("title ERROR");
            ui.CurPosition(0, 0);
            system("color 4F");
            std::cout << "\aWrong choice entered, try again! \a";
            Sleep(1500);
            system("color 0F");
            break;
        }
    }
customerPortalEnd:
    system("cls");
}

int Customer::portalMenu()
{
    int choice, i;
    char ch;
    system("color 0F");
    system("cls");
    system("title MY PORTAL");
    UI ui;
	ui.CurPosition(0, 0);
    ui.FontColor(10);
    ui.curDateAndTime();
    ui.CurPosition(0, 2);
    ui.FontColor(9);
    std::cout << "Welcome, " << this->name << std::endl;
    std::cout << "Current Balance: USD " << this->amount << std::endl;
    ui.CurPosition(32, 5);
    ui.FontColor(11);
    std::cout << "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 UNITED BANK LTD \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
    for (i = 1; i <= 14; i++)
    {
        ui.CurPosition(31, 5 + i);
        std::cout << "|";
    }
    for (i = 1; i <= 14; i++)
    {
        ui.CurPosition(91, 5 + i);
        std::cout << "|";
    }
    for (i = 1; i <= 60; i++)
    {
        ui.CurPosition(31 + i, 20);
        std::cout << "-";
    }
    ui.FontColor(15);
    ui.CurPosition(33, 7);
    std::cout << "1. View my information";
    ui.CurPosition(33, 9);
    std::cout << "2. Deposit Money";
    ui.CurPosition(33, 11);
    std::cout << "3. Withdraw Money";
    ui.CurPosition(33, 13);
    std::cout << "4. Transfer Money";
    ui.CurPosition(33, 15);
    std::cout << "5. View My Transaction History";
    ui.CurPosition(33, 17);
    std::cout << "6. Account Settings";
    ui.CurPosition(33, 19);
    std::cout << "7. Logout";
    ui.CurPosition(32, 22);
    ui.FontColor(5);
    std::cout << "Enter your choice: ";
    fflush(stdin);
    while (1)
    {
        ch = getch();
        if (ch >= '1' && ch <= '7')
        {
            std::cout << ch;
            choice = ch - '0';
        }
        else if (ch == 13)
        {
            break;
        }
        else if (ch == 8)
        {
            std::cout << "\b \b";
        }
    }
    system("color 0F");
    return choice;
}

void Customer::depositAmount()
{
    Transaction t;
    char mailContent[256], e[30];
    char transactionid[7], amt[20], bal[20];
    long long int amountToDeposit = 0;
    unsigned long long int newAmount;
    int accNo = this->accountNumber;
    char n[40];
    strcpy(n, name);
    char type[9];
    strcpy(type, "Deposit");
    while (1)
    {
    	UI ui;
        system("cls");
        std::cout << "Enter amount to deposit  ";
        ui.FontColor(1);
        std::cout << "(-1 to go back) : USD. ";
        ui.FontColor(7);
        fflush(stdin);
        std::cin >> amountToDeposit;
        if (amountToDeposit == -1)
        {
            goto amountToDepositEnd;
        }
        else if (amountToDeposit < 0)
        {
            ui.FontColor(4);
            std::cout << "\n\t\t\t\t\tAmount can not be negative" << std::endl;
            Sleep(1500);
            ui.FontColor(2000);
        }
        else
        {
            std::fstream file;
            file.open("./data/customer.bank", std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
            file.seekg(0);
            file.read((char *)this, sizeof(*this));	// reading from file
            while (file.eof() == 0)
            {
                if (this->accountNumber == accNo)
                {
                    this->amount = this->amount + amountToDeposit;
                    newAmount = this->amount;
                    strcpy(e, this->email);
                    file.seekp(file.tellp() - sizeof(*this));
                    file.write((char *)this, sizeof(*this));	// reading from file
                }
                file.read((char *)this, sizeof(*this));
            }
            file.close();
            // SetColor();
            ui.FontColor(2);
            std::cout << "\n\t\t\t\t\tUSD. " << amountToDeposit << " deposited successfully" << std::endl;
            ui.FontColor(0);
            t.storeTransaction(accNo, n, amountToDeposit, "Deposit");
            // getch();
            Sleep(2000);
            break;
        }
    }
amountToDepositEnd:
    UI ui;
	system("cls");
    ui.FontColor(7);
}

void Customer::withdrawAmount()
{
    long long int amountToWithdraw;
    char mailContent[256], amt[20], e[30];
    int accNo = this->accountNumber;
    Transaction t;
    char n[40];
    UI ui;
	strcpy(n, name);
    std::cout << "Enter amount to withdraw  ";
    ui.FontColor(1);
    std::cout << "(-1 to go back) : USD. ";
    ui.FontColor(7);
    fflush(stdin);
    std::cin >> amountToWithdraw;
    if (amountToWithdraw == -1)
    {
        goto amountToWithdrawEnd;
    }
    else if (amountToWithdraw < 0)
    {
        ui.FontColor(4);
        std::cout << "\n\t\t\t\t\tAmount can not be negative" << std::endl;
        ui.FontColor(7);
        Sleep(1500);
    }
    else if (amountToWithdraw > this->amount)
    {
        ui.FontColor(4);
        std::cout << "\n\t\t\t\t\tYou don't have enough balance" << std::endl;
        ui.FontColor(7);
        Sleep(1500);
    }
    else
    {
        std::fstream file;
        file.open("./data/customer.bank", std::ios::ate | std::ios::in | std::ios::out | std::ios::binary);
        file.seekg(0);
        file.read((char *)this, sizeof(*this));
        while (file.eof() == 0)
        {
            if (this->accountNumber == accNo)
            {
                this->amount = this->amount - amountToWithdraw;
                strcpy(e, this->email);
                file.seekp(file.tellp() - sizeof(*this));
                file.write((char *)this, sizeof(*this));	// writing to file
            }
            file.read((char *)this, sizeof(*this));
        }
        file.close();
        // SetColor();
        ui.FontColor(2);
        std::cout << "\n\t\t\t\t\tUSD. " << amountToWithdraw << " withdrawn successfully" << std::endl;
        ui.FontColor(0);
        t.storeTransaction(accNo, n, amountToWithdraw, "Withdraw");		// changing state of other object
        std::sprintf(amt, "%llu", amountToWithdraw);
        Sleep(2000);
    }
amountToWithdrawEnd:
    system("cls");
    ui.FontColor(7);
}

void Customer::transferAmount()
{
    int senderAccount = this->accountNumber;
    char receiverName[40];
    char mailContent[256], amt[20], e[30];
    strcpy(e, this->email);
    std::ifstream fin;
    Transaction t;
    char n[40];
    strcpy(n, name);
    int receiverAccount;
    long long int amountToTransfer;
    unsigned long long int senderAmount;
    senderAmount = this->amount;
    bool receiverFound = false;
    while (1)
    {
        UI ui;
		std::cout << "Enter receiver's account number  ";
        ui.FontColor(1);
        std::cout << "(-1 to go back): ";
        ui.FontColor(7);
        fflush(stdin);
        std::cin >> receiverAccount;
        system("cls");
        if (receiverAccount == senderAccount)
        {
            ui.FontColor(4);
            std::cout << "\n\t\t\t\t\tYou can not transfer to yourself" << std::endl;
            Sleep(1500);
            ui.FontColor(7);
        }
        else if (receiverAccount == -1)
        {
            goto transferAmountEnd;
        }
        else if (receiverAccount < 0)
        {
            std::cout << "Account number can not be negative" << std::endl;
            Sleep(1500);
        }
        else
        {
            break;
        }
    }
    fin.open("./data/customer.bank", std::ios::in | std::ios::binary);
    fin.read((char *)this, sizeof(*this));
    while (fin.eof() == 0)
    {
        if (this->accountNumber == receiverAccount)
        {
            receiverFound = true;
            strcpy(receiverName, name);
            break;
        }
        fin.read((char *)this, sizeof(*this));
    }
    fin.close();
    if (receiverFound == true)
    {
        UI ui;
		std::cout << "Enter amount to transfer: USD. ";
        ui.FontColor(1);
        fflush(stdin);
        std::cin >> amountToTransfer;
        if (amountToTransfer <= senderAmount && amountToTransfer >= 0)
        {
            std::fstream file;
            file.open("./data/customer.bank", std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
            file.seekg(0);
            file.read((char *)this, sizeof(*this));
            while (file.eof() == 0)
            {
                if (this->accountNumber == senderAccount)
                {
                    this->amount = this->amount - amountToTransfer;
                    file.seekp(file.tellp() - sizeof(*this));
                    file.write((char *)this, sizeof(*this));
                }
                else if (this->accountNumber == receiverAccount)
                {
                    this->amount = this->amount + amountToTransfer;
                    file.seekp(file.tellp() - sizeof(*this));
                    file.write((char *)this, sizeof(*this));
                }
                file.read((char *)this, sizeof(*this));
            }
            file.close();
            ui.FontColor(2);
            std::cout << "USD. " << amountToTransfer << " transferred successfully to " << receiverName << std::endl;
            t.storeTransaction(senderAccount, n, amountToTransfer, "Transfer");
            std::sprintf(amt, "%llu", amountToTransfer);
            Sleep(2000);
            ui.FontColor(7);
        }
        else
        {
            ui.FontColor(4);
            std::cout << "\n\t\t\t\t\tYou don't have enough balance" << std::endl;
            ui.FontColor(7);
            Sleep(1500);
        }
    }
    else
    {
        UI ui;
		ui.FontColor(4);
        std::cout << "\n\t\t\t\t\tThis account does not exists" << std::endl;
        ui.FontColor(7);
        Sleep(1500);
    }
transferAmountEnd:
    system("cls");
}

bool Customer::deleteAccount()
{
    int accNo = this->accountNumber;
    char ch, choice;
    system("cls");
    UI ui;
	ui.FontColor(4);
	bool deleted = false;
    std::cout << "Are you sure you want to delete your account? [y/n]: ";
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
        std::ifstream fin;
        std::ofstream fout;
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
            fin.read((char *)this, sizeof(*this));
            while (fin.eof() == 0)
            {
                if (this->accountNumber != accNo)
                {
                    fout.write((char *)this, sizeof(*this));
                }
                fin.read((char *)this, sizeof(*this));
            }
        }
        fin.close();
        fout.close();
        remove("./data/customer.bank");
        rename("./data/temp.bank", "./data/customer.bank");
        ui.FontColor(2);
        std::cout << "\n\t\t\t\t\tAccount deleted successfully" << std::endl;
        Bank::decrementAccountCount();
        Sleep(2500);
        deleted = true;
    }
    return deleted;
}

void Customer::accountSetting()
{
    int choice;
    while (1)
    {
    	UI ui;
        system("cls");
        std::cout << "1. Update my email" << std::endl;
        std::cout << "2. Update my contact number" << std::endl;
        std::cout << "3. Change my password" << std::endl;
        std::cout << "4. Delete my account" << std::endl;
        std::cout << "5. Go back" << std::endl;
        ui.FontColor(1);
        std::cout << std::endl
             << "Enter your choice: ";
        ui.FontColor(7);
        fflush(stdin);
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            Customer::updateEmail(this->accountNumber);
            break;
        case 2:
            Customer::updateContactNumber(this->accountNumber);
            break;
        case 3:
            Customer::changePassword(this->accountNumber);
            break;
        case 4:
            if(Customer::deleteAccount() == true){
            	goto customerAccountSettingEnd;
			}
            break;
        case 5:
            goto customerAccountSettingEnd;
            break;
        default:
            ui.FontColor(4);
            std::cout << "Enter a valid choice" << std::endl;
            Sleep(1000);
            ui.FontColor(7);
            break;
        }
    }
customerAccountSettingEnd:
    system("cls");
}

void Customer::updateInfo(int accNo)
{
    std::fstream file;
    Customer c;
    file.open("./data/customer.bank", std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
    file.seekg(0);
    file.read((char *)&c, sizeof(c));
    while (file.eof() == 0)
    {
        if (c.accountNumber == accNo)
        {
            file.seekp(file.tellp() - sizeof(c));
            file.write((char *)this, sizeof(*this));
            break;
        }
        file.read((char *)&c, sizeof(c));
    }
    file.close();
}

void Customer::updateEmail(int accNo)
{
    setEmail();
    system("cls");
    std::cout << "Enter your password to confirm: ";
    char passToConfirm[20];
    inputPassword(passToConfirm);
    if (strcmp(password, passToConfirm) == 0)
    {
        Customer::updateInfo(accNo);
    }
}

void Customer::updateContactNumber(int accNo)
{
    setContactNumber();
    system("cls");
    std::cout << "Enter your password to confirm: ";
    char passToConfirm[20];
    inputPassword(passToConfirm);
    if (strcmp(password, passToConfirm) == 0)
    {
        Customer::updateInfo(accNo);
    }
}

void Customer::changePassword(int accNo)
{
    char passToConfirm[20];
    std::cout << "Enter your password to confirm: ";
    inputPassword(passToConfirm);
    if (strcmp(password, passToConfirm) == 0)
    {
        system("cls");
        system("title ENTER NEW PASSWORD");
        setPassword();
        Customer::updateInfo(accNo);
    }
}

