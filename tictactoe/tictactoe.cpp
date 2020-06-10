#include <iostream>
#include <string>

using namespace std;

constexpr char g_emptyCell = '-';

struct Table {
    char row1[3];
    char row2[3];
    char row3[3];
};

// Game flow functions
void mainGameLoop(Table &table);
void userMakesMove(Table &table, char mark);
void updateTable(Table &table, std::string userPos, char mark);

// Print functions
void printTable(Table &table);
void printRow(char *row, int rowAnnot);
void printColsAnnots();
void printBorder();

// Input functions
string getUserPos(Table &table, char mark);

// Helper functions
char* getRow(Table &table, std::string pos);
int getIndex(Table &table, std::string pos);

// Check functions
bool checkDraw(Table &table);
bool checkWin(Table &table, char mark);
bool checkHorizontalWin(Table &table, char mark);
bool checkVerticalWin(Table &table, char mark);
bool checkDiagonalWin(Table &table, char mark);
bool checkUserPos(std::string pos);
bool checkTable(Table &table, std::string pos);

int main()
{
    Table table { { g_emptyCell, g_emptyCell, g_emptyCell },
                  { g_emptyCell, g_emptyCell, g_emptyCell },
                  { g_emptyCell, g_emptyCell, g_emptyCell }, };

    printTable(table);
    mainGameLoop(table);

    return 0;
}

void mainGameLoop(Table &table)
{
    char xMark = 'X', oMark = 'O';

    for (;;) {
        userMakesMove(table, xMark);
        userMakesMove(table, oMark);
    }
}

void userMakesMove(Table &table, char mark)
{
    string userPos = getUserPos(table, mark);
    updateTable(table, userPos, mark);
    printTable(table);

    if (checkWin(table, mark)) {
        cout << "( " << mark << " ) You won!\n";
        exit(0);
    } else if (checkDraw(table)) {
        cout << "Draw!\n";
        exit(0);
    }
}

void updateTable(Table &table, string userPos, char mark)
{
    char* row = getRow(table, userPos);
    int index = getIndex(table, userPos);
    row[index] = mark;
}


string getUserPos(Table &table, char mark)
{
    for (;;) {
        cout << "( " << mark << " ) Enter position: ";
        string pos;
        cin >> pos;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            continue;
        }
        // Check if input size is 2
        if (pos.size() != 2) {
            cin.ignore(32767, '\n');
            continue;
        }
        // Check if input is valid (first char is 1 or 2 or 3, second char is a or b or c)
        if (!checkUserPos(pos)) {
            cin.ignore(32767, '\n');
            continue;
        }
        // Check if postion is free on the table
        if (!checkTable(table, pos)) {
            cin.ignore(32767, '\n');
            continue;
        }
        cin.ignore(32767, '\n');
        return pos;
    }
}

char* getRow(Table &table, string pos)
{
    switch (pos[0]) {
    case '1': return table.row1;
    case '2': return table.row2;
    case '3': return table.row3;
    default: return nullptr;
    }
}

int getIndex(Table &table, string pos)
{
    switch (pos[1]) {
    case 'A': return 0;
    case 'B': return 1;
    case 'C': return 2;
    default: return -1;
    }
}

bool checkDraw(Table &table)
{
    for (int i = 0; i < 3; ++i) {
        if (table.row1[i] == g_emptyCell || table.row2[i] == g_emptyCell ||
            table.row3[i] == g_emptyCell)
            return false;
    }
    return true;
}

bool checkWin(Table &table, char mark)
{
    return checkHorizontalWin(table, mark) || checkVerticalWin(table, mark) ||
           checkDiagonalWin(table, mark);
}

bool checkDiagonalWin(Table &table, char mark)
{
    if (table.row1[0] == mark && table.row2[1] == mark && table.row3[2] == mark)
        return true;
    if (table.row3[0] == mark && table.row2[1] == mark && table.row1[2] == mark)
        return true;
    return false;
}

bool checkVerticalWin(Table &table, char mark)
{
    for (int i = 0; i < 3; ++i)
        if (table.row1[i] == mark && table.row2[i] == mark && table.row3[i] == mark)
            return true;
    return false;
}

bool checkHorizontalWin(Table &table, char mark)
{
    if (table.row1[0] == mark && table.row1[1] == mark && table.row1[2] == mark)
        return true;
    if (table.row2[0] == mark && table.row2[1] == mark && table.row2[2] == mark)
        return true;
    if (table.row3[0] == mark && table.row3[1] == mark && table.row3[2] == mark)
        return true;
    return false;
}

// Checks if a position is empty.
bool checkTable(Table &table, string pos)
{
    char* p_row = getRow(table, pos);
    int index = getIndex(table, pos);
    return p_row[index] == g_emptyCell;
}

// Checks if user input position is valid
bool checkUserPos(string pos)
{
    bool first = false, second = false;

    switch (pos[0]) {
    case '1': case '2': case '3':
        first = true;
    }

    switch (pos[1]) {
    case 'A': case 'B': case 'C':
        second = true;
    }

    return first && second;
}

void printTable(Table &table)
{
    printColsAnnots();
    printRow(table.row1, 1);
    printRow(table.row2, 2);
    printRow(table.row3, 3);
}

void printRow(char *row, int rowAnnot)
{
    cout << " " << rowAnnot << " | ";
    for (int i {0}; i < 3; ++i)
        cout << row[i] << " | ";
    printBorder();
}

void printColsAnnots()
{
    cout << "     A " << "  B " << "  C ";
    printBorder();
}

void printBorder()
{
    cout << '\n';
    cout << "   -------------\n";
}
