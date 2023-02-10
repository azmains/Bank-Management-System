#include "UI.h"

void UI::CurPosition(int x, int y)
{

    COORD c;
    c.X = x;
    c.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}



void UI::loadAnimation()
{
    int i;
    system("cls");
    system("color 0A");
    CurPosition(56, 10);
    std::cout << "Loading";
    CurPosition(40, 12);
    printf("[");
    CurPosition(78, 12);
    printf("]");
    CurPosition(41, 12);
    for (i = 1; i <= 37; i++)
    {
        printf("%c", 177);
    }
    CurPosition(41, 12);
    for (i = 1; i <= 37; i++)
    {
        Sleep(30);
        printf("%c", 219);
    }
    CurPosition(0, 0);
    system("cls");
    system("color 0F");
}

void UI::FontColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // We use csbi for the wAttributes word.
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        // Mask out all but the background attribute, and add in the forgournd     color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

void UI::curDateAndTime()
{
    time_t t; // not a primitive datatype
    time(&t);

    std::cout << ctime(&t);
}

void UI::TextSize(int x, int y)
{

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = x; // Width of each character in the font
    cfi.dwFontSize.Y = y; // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = 700;                  // For normal: FW_NORMAL
    std::wcscpy(cfi.FaceName, L"Courier"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void UI::Box()
{
    CurPosition(40, 7);
    FontColor(1);
    for (int i = 0; i < 40; i++)
        std::cout << "-";
    FontColor(2);
    CurPosition(44, 13);
    std::cout << "ThankYou for using Our Service:)";
    FontColor(1);
    for (int i = 0; i < 11; i++)
    {
        CurPosition(39, 8 + i);
        std::cout << "|\n";
    }
    CurPosition(40, 19);
    for (int i = 0; i < 40; i++)
        std::cout << "-";
    for (int i = 0; i < 11; i++)
    {
        CurPosition(80, 8 + i);
        std::cout << "|\n";
    }
    std::cout << std::endl;
}

int UI::MainMenu()
{
    int choice, i;
    char ch;
    system("color 0F");
    system("cls");
    system("BANK - MAIN MENU");
    CurPosition(0, 0);
    FontColor(10);
    curDateAndTime();
    CurPosition(32, 3);
    TextSize(0, 21);
    FontColor(11);
    std::cout << "\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 UNITED BANK LTD \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2";
    for (i = 1; i <= 8; i++)
    {
        CurPosition(31, 3 + i);
        printf("|");
    }
    for (i = 1; i <= 8; i++)
    {
        CurPosition(91, 3 + i);
        printf("|");
    }
    for (i = 1; i <= 60; i++)
    {
        CurPosition(31 + i, 12);
        printf("-");
    }
    FontColor(15);
    CurPosition(33, 5);
    std::cout << "1. Login as Admin";
    CurPosition(33, 6);
    std::cout << "2. Login as Customer";
    CurPosition(33, 7);
    std::cout << "3. Create new account";
    CurPosition(33, 8);
    std::cout << "4. Check today's currency rates";
    CurPosition(33, 9);
    std::cout << "5. About Us";
    CurPosition(33, 10);
    std::cout << "6. Taxation Department";
    CurPosition(33, 11);
    std::cout << "7. Exit";
    CurPosition(32, 15);
    std::cout << "Enter your choice: ";
    i = 0;
    while (1)
    {
    	fflush(stdin);
        ch = getch();
        if (ch >= '1' && ch <= '7' && i == 0)
        {
            std::cout << ch;
            choice = ch - '0';
            i++;
        }
        else if (ch == 13 && i == 1)
        {
            break;
        }
        else if (ch == 8 && i != 0)
        {
            i--;
            std::cout << "\b \b";
        }
    }
    return choice;
}

void UI::AboutUs()
{
    system("cls");
    int j;
    for (j = 21; j >= 0; j--)
    {
        if (j == 21)
        {
            system("color 01");
        }
        if (j == 19)
        {
            system("color 02");
        }
        if (j == 18)
        {
            system("color 03");
        }
        if (j == 17)
        {
            system("color 04");
        }
        if (j == 16)
        {
            system("color 05");
        }
        if (j == 15)
        {
            system("color 06");
        }
        if (j == 14)
        {
            system("color 07");
        }
        if (j == 13)
        {
            system("color 08");
        }
        if (j == 12)
        {
            system("color 09");
        }
        if (j == 11)
        {
            system("color 0A");
        }
        if (j == 10)
        {
            system("color 0B");
        }
        if (j == 9)
        {
            system("color 0C");
        }
        if (j == 8)
        {
            system("color 0D");
        }
        if (j == 7)
        {
            system("color 0E");
        }
        if (j == 6)
        {
            system("color 0F");
        }
        if (j == 5)
        {
            system("color 01");
        }
        if (j == 4)
        {
            system("color 02");
        }
        if (j == 3)
        {
            system("color 03");
        }
        if (j == 2)
        {
            system("color 0C");
        }
        if (j == 1)
        {
            system("color 0E");
        }
        if (j == 0)
        {
            system("color 0F");
        }
        system("cls");
        CurPosition(46, j - 1);
        printf("THIS SYSTEM IS DESIGNED BY");
        CurPosition(46, j + 1);
        printf("Name   (Roll No)");
        CurPosition(46, j + 2);
        printf("Name   (Roll No)");
        CurPosition(46, j + 3);
        printf("Name   (Roll No)");
        CurPosition(0, 0);
        Sleep(600);
    }
}

