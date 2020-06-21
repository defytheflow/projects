/*
 *  File: baseconvert.cpp
 *
 *  Description:
 *    Конвертирует число из одной системы счисления в другую.
 *
 *  Input:
 *    number     (число)
 *    base_from  (система счисления "ИЗ")
 *    base_to    (cистема счисления "В")
 *
 *  Output:
 *    Число в системе счисления "В"
 *
 *  Example:
 *    Enter number:     112D
 *    Enter base_from:  16
 *    Enter base_to:    8
 *
 *    Result:           10455
 *
 *  Issues:
 *    1. Нужно добавить поддержку негативных чисел.
 *    2. It doesn't work properly.
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <windows.h>

#define DEBUG

using namespace std;

enum Base {
    BIN = 2,
    OCT = 8,
    DEC = 10,
    HEX = 16,
};

enum Color {
    RED    = 12,
    GREEN  = 10,
    YELLOW = 14,
    WHITE  = 15,
};

void print(const char* str, int color);
void error(const char* msg);

string get_string(const char* prompt);
int get_int(const char* prompt);

void to_uppercase(string& number);
void remove_spaces(string& number);

bool isfloat(const string& number);
bool isbase(const string& number, int base);

bool base_supported(int base);

bool is_valid_number_of_base(const string& number, int base_from);

int convert_to_decimal(const string& number, int base_from);
string convert_decimal_to_base(int decimal_number, int base_to);

char to_hexadecimal(int n);
string base_to_string(int base);

int main()
{
    system("cls");

    string number, result;
    int base_from, base_to, decimal_number;

    number = get_string("\nEnter number: ");

    remove_spaces(number);
    to_uppercase(number);

    if (isfloat(number))
        error("Floating point numbers are not supported");

    base_from = get_int("Enter base from (2|8|10|16): ");

    if (!base_supported(base_from))
        error("Invalid base from. Only (2|8|10|16) bases are supported");

    if (!is_valid_number_of_base(number, base_from))
        error((string("Invalid number of base ") + base_to_string(base_from)).c_str());

    base_to = get_int("Enter base to (2|8|10|16): ");

    if (!base_supported(base_to))
        error("Invalid base to. Only (2|8|10|16) bases are supported");

    cout << '\n';

#ifdef DEBUG
    print("Number: ", YELLOW);
    cout << number << endl;
#endif

    decimal_number = convert_to_decimal(number, base_from);

#ifdef DEBUG
    print("Decimal: ", YELLOW);
    cout << decimal_number << endl;
#endif

    result = convert_decimal_to_base(decimal_number, base_to);

    print("Result: ", GREEN);
    cout << result << endl;

    return EXIT_SUCCESS;
}

/*
 * Печатает в консоль цветом.
 */
void print(const char* str, int color)
{
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_handle, color);
    cerr << str;
    SetConsoleTextAttribute(console_handle, WHITE);  // 15 - Белый цвет
}

/*
 * Печатает сообщение об ошибке в консоль и завершает выполнение программы с
 * сигналом неудачного выполнения для операционной системы.
 */
void error(const char* msg)
{
    print("\nError: ", RED);
    cerr << msg << endl;
    exit(EXIT_FAILURE);
}

/*
 * Возвращает введенную пользователем строку.
 */
string get_string(const char* prompt)
{
    string input;

    cout << prompt;
    std::getline(cin, input);

    if (cin.fail())
        error("Input failed");

    return input;
}

/*
 * Возвращает введенное пользователем целое число.
 */
int get_int(const char* prompt)
{
    int input;

    cout << prompt;
    cin >> input;

    if (cin.fail())
        error("Input failed");

    return input;
}

/*
 * Удаляет из строки символы пробела и табуляции.
 */
void remove_spaces(string& str)
{
   for (int i = 0, len = str.length(); i < len; ++i) {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\r') {
            str.erase(i, 1);
            len = str.length(); // Обновляем длину, так как мы удалили один символ
            --i;  // Не изменяем следующий индекс, потому что нужно проверить
         //  новый символ, который стал на место удаленного
        }
    }
}

/*
 * Заменяет все символы нижнего регистра в строке 'str' на соответствующие
 * символы верхнего регистра.
 */
void to_uppercase(string& str)
{
    for (int i = 0; i < str.length(); ++i) {
        if ('a' <= str[i] && str[i] <= 'z')
            str.replace(i, 1, 1, str[i] - 32);
    }
}

/*
 * Возвращает правду если в Cтроке 'number' присутствует символ '.'.
 */
bool isfloat(const string& number)
{
    for (int i = 0; i < number.length(); ++i) {
        if (number[i] == '.')
            return true;
    }
    return false;
}

/*
 * Возвращает правду если система счисления 'base' поддерживается программой.
 */
bool base_supported(int base)
{
    switch (base) {
    case BIN:
    case OCT:
    case DEC:
    case HEX: return true;
    default:  return false;
    }
}

/*
 * Возвращает правду если Строка 'number' состоит из "легальных" символов для
 * системы счисления 'base_from'.
 */
bool is_valid_number_of_base(const string& number, int base_from)
{
    switch (base_from) {
    case BIN: return isbase(number, BIN) ? true : false;
    case OCT: return isbase(number, OCT) ? true : false;
    case DEC: return isbase(number, DEC) ? true : false;
    case HEX: return isbase(number, HEX) ? true : false;
    default:  return false; // Shouldn't reach.
    }
}

/*
 * Возвращает правду если Строка 'number' состоит только  из символов
 * "легальных" в Системе Счисления 'base'.
 */
bool isbase(const string& number, int base)
{
    switch (base) {
    case BIN:
    case OCT:
    case DEC:
        for (int i = 0; i < number.length(); ++i)
            if (!('0' <= number[i] && number[i] <= base-1 + '0'))
                return false;
        return true;
    case HEX:
        for (int i = 0; i < number.length(); ++i)
            if (!(('0' <= number[i] && number[i] <= '9') ||
                  ('A' <= number[i] && number[i] <= 'F')))
                return false;
        return true;
    default: // Не должно до сюда доходить
        return false;
    }
}

/*
 * Возвращает результат конверсии Десятичного числа 'decimal_number' в
 * систему счисления 'base_to'.
 */
string convert_decimal_to_base(int decimal_number, int base_to)
{
    int remainder;
    string result;

    for (;decimal_number != 0; decimal_number /= base_to) {
        remainder = decimal_number % base_to;
        if (10 <= remainder && remainder <= 15)
            result.push_back(to_hexadecimal(remainder));
        else
            result.push_back(remainder + '0');
    }

    std::reverse(result.begin(), result.end());
    return result;
}

/*
 * Возвращает результат конверсии 'number' из Системы Счисления 'base_from'
 * в Десятичную.
 */
int convert_to_decimal(const string& number, int base_from)
{
    int result = 0;

    for (int i = number.length() - 1, j = 0; i >= 0; --i, ++j)
        result += (number[i] - '0') * std::pow(base_from, j);

    return result;
}

/*
 * Возвращает название Cистемы Cчисления в виде строки.
 */
string base_to_string(int base)
{
    switch (base) {
    case BIN: return "binary";
    case OCT: return "octal";
    case DEC: return "decimal";
    case HEX: return "hexadecimal";
    default:  return ""; // Shouldn't reach it.
    }
}

/*
 * Принимает целое число n в промежутке от 10 до 15,
 * Возвращает эквивалент в 16 Системе Счисления.
 */
char to_hexadecimal(int n)
{
    switch (n) {
    case 10: return 'A';
    case 11: return 'B';
    case 12: return 'C';
    case 13: return 'D';
    case 14: return 'E';
    case 15: return 'F';
    default: return '\0';
    }
}
