#include <iostream>
#include <cstring>

using namespace std;

const char *RED = "\033[31m";
const char *GREEN = "\033[32m";
const char *YELLOW = "\033[33m";
const char *BLUE = "\033[34m";
const char *GRAY = "\033[90m";
const char *RESET = "\033[0m";

void printSizes()
{
    cout << "bool: " << sizeof(bool) << endl
         << "char: " << sizeof(char) << endl
         << "short int: " << sizeof(short int) << endl
         << "int: " << sizeof(int) << endl
         << "long int: " << sizeof(long int) << endl
         << "long long: " << sizeof(long long) << endl
         << "float: " << sizeof(float) << endl
         << "double: " << sizeof(double) << endl
         << "long double: " << sizeof(long double) << endl;
}

void printBits(int num)
{
    const int orderInt = sizeof(num) * 8;
    unsigned int mask = 1u << (orderInt - 1);

    for (int i = 0; i < orderInt; i++)
    {
        char bit = (num & (mask >> i)) ? '1' : '0';
        if ((i != 0) && (i % 4 == 0))
        {
            cout << " ";
        }
        else if (i == 0)
        {
            cout << RED << bit;
            continue;
        }
        else if (i == 1)
        {
            cout << GRAY << " | " << RESET;
        }
        cout << YELLOW << bit << RESET;
    }
    cout << endl;
}

void printBits(float num)
{
    unsigned int bits;
    memcpy(&bits, &num, sizeof(bits));

    const int orderInt = sizeof(num) * 8;
    unsigned int mask = 1u << (orderInt - 1);

    for (int i = 0; i < orderInt; i++)
    {
        char bit = (bits & (mask >> i)) ? '1' : '0';
        if (i == 1 || i == 9)
        {
            cout << GRAY << " | " << RESET;
        }
        if ((i == 0))
        {
            cout << RED << bit << RESET;
        }
        else if ((i > 0) && (i <= 8))
        {
            cout << GREEN << bit << RESET;
        }
        else
        {
            cout << BLUE << bit << RESET;
        }
    }
    cout << endl;
}

void printBits(double num)
{
    unsigned long long bits;
    memcpy(&bits, &num, sizeof(bits));

    const int orderInt = sizeof(num) * 8;
    unsigned long long mask = 1ull << (orderInt - 1);

    for (int i = 0; i < orderInt; i++)
    {
        char bit = (bits & (mask >> i)) ? '1' : '0';
        if (i == 1 || i == 12)
        {
            cout << GRAY << " | " << RESET;
        }
        if ((i == 0))
        {
            cout << RED << bit << RESET;
        }
        else if ((i > 0) && (i <= 11))
        {
            cout << GREEN << bit << RESET;
        }
        else
        {
            cout << BLUE << bit << RESET;
        }
    }
    cout << endl;
}

int changeBit(int num, int k, int op)
{
    unsigned int bits;
    memcpy(&bits, &num, sizeof(num));
    unsigned int mask = 1u << k;

    if (op == 1)
    {
        bits |= mask;
    }
    else if (op == 0)
    {
        bits &= ~mask;
    }
    else if (op == -1)
    {
        bits ^= mask;
    }
    memcpy(&num, &bits, sizeof(num));
    return num;
}

float changeBit(float num, int k, int op)
{
    unsigned int bits;
    memcpy(&bits, &num, sizeof(num));
    unsigned int mask = 1u << k;

    if (op == 1)
    {
        bits |= mask;
    }
    else if (op == 0)
    {
        bits &= ~mask;
    }
    else if (op == -1)
    {
        bits ^= mask;
    }
    memcpy(&num, &bits, sizeof(num));
    return num;
}

double changeBit(double num, int k, int op)
{
    unsigned long long bits;
    memcpy(&bits, &num, sizeof(num));
    unsigned long long mask = 1ull << k;

    if (op == 1)
    {
        bits |= mask;
    }
    else if (op == 0)
    {
        bits &= ~mask;
    }
    else if (op == -1)
    {
        bits ^= mask;
    }
    memcpy(&num, &bits, sizeof(num));
    return num;
}

int invertSign(int num)
{
    return ~num + 1;
}

float invertSign(float num)
{
    return changeBit(num, sizeof(num) * 8 - 1, -1);
}

double invertSign(double num)
{
    return changeBit(num, sizeof(num) * 8 - 1, -1);
}

int main()
{
    printSizes();

    cout << "\n--- int ---\n";
    cout << " 5:  ";
    printBits(5);
    cout << "-5:  ";
    printBits(-5);
    cout << " 0:  ";
    printBits(0);

    cout << "\n--- float ---\n";
    cout << " 3.14f: ";
    printBits(3.14f);
    cout << "-2.5f: ";
    printBits(-2.5f);
    cout << " 0.0f: ";
    printBits(0.0f);
    cout << "1e-40f: ";
    printBits(1e-40f);
    cout << "+inf: ";
    printBits(1.0f / 0.0f);
    cout << "-inf: ";
    printBits(-1.0f / 0.0f);
    cout << "NaN: ";
    printBits(0.0f / 0.0f);

    cout << "\n--- double ---\n";
    cout << " 3.14: ";
    printBits(3.14);
    cout << "-2.5: ";
    printBits(-2.5);

    cout << "\n--- changeBit ---\n";
    int v = 0;
    v = changeBit(v, 3, 1); // установить бит 3
    cout << "set bit3: ";
    printBits(v);
    v = changeBit(v, 3, 0); // сбросить
    cout << "clr bit3: ";
    printBits(v);
    v = changeBit(v, 3, -1); // инвертировать
    cout << "inv bit3: ";
    printBits(v);

    cout << "\n--- invertSign ---\n";
    int num = 5;
    cout << "invertSign(5) = " << invertSign(num) << endl;
    cout << "before: ";
    printBits(num);
    cout << "after: ";
    printBits(invertSign(num));

    float numf = 3.14f;
    cout << "invertSign(3.14f) = " << invertSign(numf) << endl;
    cout << "before: ";
    printBits(numf);
    cout << "after: ";
    printBits(invertSign(numf));
}