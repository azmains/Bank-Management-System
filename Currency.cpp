#include "Currency.h"
#include "UI.h"
//#include "main.cpp"


int Currency::generateCurrencyCode()
{
    std::ifstream fin;
    int num;
    bool isFound = false;
    srand(time(0));
    fin.open("./data/currency.bank", std::ios::in | std::ios::binary);
    if (!fin)
    {
        std::cout << "File does not exists" << std::endl;
    }
    else
    {
        while (1)
        {
            num = (rand() % 90) + 10;
            fin.read((char *)this, sizeof(*this));
            while (fin.eof() == 0)
            {
                if (this->code == num)
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

void Currency::addCurrency()
{
    char ch;
    int i;
    i = 0;
    std::ofstream fout;
    this->code = generateCurrencyCode();
    std::cout << "Enter currency name: ";
    UI ui;
	ui.FontColor(2);
    fflush(stdin);
    gets(name);
    system("cls");
    ui.FontColor(7);
    std::cout << "Enter symbol (3 characters): ";
    ui.FontColor(2);
    while (1)
    {
    	fflush(stdin);
        ch = getch();
        if (ch >= 'A' && ch <= 'Z' && i < 3)
        {
            std::cout << ch;
            symbol[i] = ch;
            i++;
        }
        else if (ch >= 'a' && ch <= 'z' && i < 3)
        {
            ch = ch - 32;
            std::cout << ch;
            symbol[i] = ch;
            i++;
        }
        else if (i == 3 && ch == 13)
        {
            break;
        }
    }
    symbol[3] = '\0';
    system("cls");
    ui.FontColor(7);
    std::cout << "Enter rate of " << name << ": ";
    ui.FontColor(2);
    fflush(stdin);
    float r;
    std::cin >> r;
    setRate(r);
    fout.open("./data/currency.bank", std::ios::app | std::ios::binary);
    fout.write((char *)this, sizeof(*this));
    fout.close();
    ui.FontColor(2);
    std::cout << "\n\t\t\t\t\tCurrency added successfully" << std::endl;
    Sleep(1500);
    ui.FontColor(7);
}

void Currency::updateCurrencyRate()
{
    system("cls");
    int code1;
    viewCurrencyRates();
    std::cout << "\nEnter currency code to update: ";
    std::cin >> code1;
    bool found = false;
    std::fstream file;
    std::ifstream fin;
    float r1;
    fin.open("./data/currency.bank", std::ios::in | std::ios::binary);
    if (!fin)
    {
        perror("Error");
        Sleep(1500);
        exit(1);
    }
    fin.read((char *)this, sizeof(*this));
    while (fin.eof() == 0)
    {
        if (this->code == code1)
        {
            found = true;
            break;
        }
        fin.read((char *)this, sizeof(*this));
    }
    fin.close();
    if (found == true)
    {
        std::cout << "Enter new rate: ";
        std::cin >> r1;
        file.open("./data/currency.bank", std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
        file.seekg(0);
        file.read((char *)this, sizeof(*this));
        while (file.eof() == 0)
        {
            if (this->code == code1)
            {
                setRate(r1);
                file.seekp(file.tellp() - sizeof(*this));
                file.write((char *)this, sizeof(*this));
            }
            file.read((char *)this, sizeof(*this));
        }
        file.close();
        system("cls");
        UI ui;
		ui.FontColor(2);
        std::cout << "Rate update successfully" << std::endl;
        ui.FontColor(7);
    }
    else
    {
        UI ui;
		ui.FontColor(4);
        system("cls");
        std::cout << "This currency does not exists, enter valid code" << std::endl;
        ui.FontColor(7);
    }
    Sleep(1500);
}

void Currency::setRate(float rate)
{
    if (rate < 0)
    {
        this->rate = 0.0;
    }
    else
    {
        this->rate = rate;
    }
}

void Currency::addCurrency(int code, char n[25], char s[4], float rate)
{
    this->code = code;
    strcpy(name, n);
    strcpy(symbol, s);
    this->rate = rate;
    std::ofstream fout;
    fout.open("./data/currency.bank", std::ios::app | std::ios::binary);
    fout.write((char *)this, sizeof(*this));
    fout.close();
}

void Currency::viewCurrencyRates() const
{
    UI ui;
	ui.TextSize(0, 15);
    std::ifstream fin;
    fin.open("./data/currency.bank", std::ios::in | std::ios::binary);
    fin.read((char *)this, sizeof(*this));
    system("color F1");
    std::cout << "Code              Name     Symbol  Rate" << std::endl;
    ui.FontColor(3);
    while (fin.eof() == 0)
    {
        std::cout << this->code << std::setw(20) << this->name << "     " << this->symbol << "     " << this->rate << std::endl;
        fin.read((char *)this, sizeof(*this));
    }
    fin.close();
    ui.FontColor(1);
    std::cout << std::endl
         << "Press any key to continue...";
    getch();
    ui.FontColor(7);
    ui.TextSize(0, 21);
}

