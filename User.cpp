#include "User.h"
#include "UI.h"
//#include "main.cpp"


void User::setName()
{
    char ch;
    int i, backspaceCount;
    backspaceCount = i = 0;
    std::cout << "Enter your full name: ";
    while (1)
    {
        ch = getch();
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch == 32))
        {
            this->name[i] = ch;
            std::cout << ch;
            i++;
            backspaceCount++;
        }
        else if (ch == 8 && backspaceCount > 0)
        {
            std::cout << "\b \b";
            i--;
            backspaceCount--;
        }
        else if (ch == 13)
        {
            break;
        }
    }
    this->name[i] = '\0';
}

void User::setAge()
{
    char ch, a[3];
    int i, backspaceCount;
    backspaceCount = i = 0;
    std::cout << "Enter your age : ";
    while (1)
    {
        ch = getch();
        if (ch >= '0' && ch <= '9')
        {
            a[i] = ch;
            std::cout << ch;
            i++;
            backspaceCount++;
        }
        else if (ch == 8 && backspaceCount > 0)
        {
            std::cout << "\b \b";
            i--;
            backspaceCount--;
        }
        else if (ch == 13 && i == 2)
        {
            break;
        }
    }
    a[3] = '\0';
    this->age = ((a[0] - 48) * 10) + (a[1] - 48);
    if (this->age < 18)
    {
    	UI ui;
        ui.FontColor(4);
        std::cout << "\n\t\t\t\t\tAge must be greater than or equal to 18" << std::endl;
        ui.FontColor(7);
        setAge();
    }
}

void User::setGender()
{
    char ch;
    std::cout << "Enter your gender (m:male, f:female): ";
    while (1)
    {
        ch = getch();
        if (ch == 'm' || ch == 'f')
        {
            this->gender = ch;
            std::cout << ch;
            break;
        }
    }
}

void User::setCNIC()
{
    char ch;
    int i, backspaceCount;
    backspaceCount = i = 0;
    std::cout << "Enter your CNIC (without dash) : ";
    while (1)
    {
        ch = getch();
        if (ch >= '0' && ch <= '9')
        {
            this->cnic[i] = ch;
            std::cout << ch;
            i++;
            backspaceCount++;
        }
        else if (ch == 8 && backspaceCount > 0)
        {
            std::cout << "\b \b";
            i--;
            backspaceCount--;
        }
        else if (ch == 13 && i == 13)
        {
            break;
        }
    }
    this->cnic[13] = '\0';
}

void User::setContactNumber()
{
    char ch;
    int i, backspaceCount;
    backspaceCount = i = 0;
    std::cout << "Enter your contact number: ";
    while (1)
    {
        ch = getch();
        if (ch >= '0' && ch <= '9')
        {
            this->contactNumber[i] = ch;
            std::cout << ch;
            i++;
            backspaceCount++;
        }
        else if (ch == 8 && backspaceCount > 0)
        {
            std::cout << "\b \b";
            i--;
            backspaceCount--;
        }
        else if (ch == 13 && i == 11)
        {
            break;
        }
    }
    this->contactNumber[11] = '\0';
}

void User::setEmail()
{
    char ch;
    int i, backspaceCount;
    backspaceCount = i = 0;
    std::cout << "Enter your email: ";
    while (1)
    {
        ch = getch();
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch == 32) || (ch == '@') || (ch == '.') || (ch >= '0' && ch <= '9'))
        {
            this->email[i] = ch;
            std::cout << ch;
            i++;
            backspaceCount++;
        }
        else if (ch == 8 && backspaceCount > 0)
        {
            std::cout << "\b \b";
            i--;
            backspaceCount--;
        }
        else if (ch == 13)
        {
            break;
        }
    }
    this->email[i] = '\0';
}

void User::setPassword()
{
	UI ui;
    char ch;
    int i, backspaceCount;
    backspaceCount = i = 0;
    std::cout << "Enter your password: ";
    ui.FontColor(4);
    while (1)
    {
        ch = getch();
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch == 32) || (ch == '@') || (ch == '.') || (ch >= '0' && ch <= '9'))
        {
            this->password[i] = ch;
            std::cout << '*';
            i++;
            backspaceCount++;
        }
        else if (ch == 8 && backspaceCount > 0)
        {
            std::cout << "\b \b";
            i--;
            backspaceCount--;
        }
        else if (ch == 13)
        {
            break;
        }
    }
    this->password[i] = '\0';
    ui.FontColor(15);
}

void User::readData()
{
    std::ifstream fin;
    system("cls");
    fin.open("./data/customer.bank", std::ios::in | std::ios::binary);
    fin.read((char *)this, sizeof(*this));		// reading from file
    while (fin.eof() == 0)
    {
        std::cout << "Acc No: " << this->accountNumber << std::endl;
        std::cout << "Name: " << this->name << std::endl;
        std::cout << "Email: " << this->email << std::endl;
        std::cout << "CNIC: " << this->cnic << std::endl;
        std::cout << std::endl;
        fin.read((char *)this, sizeof(*this));		// reading from file
    }
    fin.close();
}

void User::inputPassword(char pass[20])
{
    UI ui;
	char ch;
    int i, backspaceCount;
    backspaceCount = i = 0;
    ui.FontColor(4);
    while (1)
    {
        ch = getch();
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch == 32) || (ch == '@') || (ch == '.') || (ch >= '0' && ch <= '9'))
        {
            pass[i] = ch;
            std::cout << '*';
            i++;
            backspaceCount++;
        }
        else if (ch == 8 && backspaceCount > 0)
        {
            std::cout << "\b \b";
            i--;
            backspaceCount--;
        }
        else if (ch == 13)
        {
            break;
        }
    }
	ui.FontColor(15);
    pass[i] = '\0';
}

int User::getAccountNumber()
{
    return accountNumber;
}

char *User::getName()
{
    return name;
}

int User::getAge()
{
    return age;
}

char User::getGender()
{
    return gender;
}

char *User::getContactNumber()
{
    return contactNumber;
}

char *User::getCNIC()
{
    return cnic;
}

char *User::getEmail()
{
    return email;
}

