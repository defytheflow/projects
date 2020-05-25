#include <ctime>
#include <iostream>
#include <random>

using namespace std;

int generate_random_int(int low, int high);
void print_rules();
void game_mainloop(int num);
int get_int();
void ask_to_play_again();

constexpr int LOW = 1;
constexpr int HIGH = 100;
constexpr int ATTEMPTS_LIMIT = 7;

int g_attempts = 1;

int main()
{
    int num = generate_random_int(LOW, HIGH);

    print_rules();
    while (g_attempts <= ATTEMPTS_LIMIT)
        game_mainloop(num);

    cout << "Sorry, you lost. The correct number was " << num << '\n';
    ask_to_play_again();

    return 0;
}

void game_mainloop(int num)
{
    int guess = get_int();
    ++g_attempts;

    if (guess > num)
        cout << "Your guess is too high.\n";
    else if (guess < num)
        cout << "Your guess is too low.\n";
    else {
        cout << "Correct! You won!\n";
        ask_to_play_again();
    }
}

void ask_to_play_again()
{
    for (;;) {
        cout << "Would you like to play again (y/n)? ";
        char ans;
        cin >> ans;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(32677, '\n');
            continue;
        }

        cin.ignore(32677, '\n');

        switch (ans) {
        case 'y':
        case 'Y':
            g_attempts = 1;
            main();
        case 'n':
        case 'N':
            cout << "Thank you for playing.\n";
            exit(0);
        }
    }
}

int get_int()
{
    for (;;) {
        cout << "Guess #" << g_attempts << ": ";
        int guess;
        cin >> guess;

        if (cin.fail())
            cin.clear();
        else
            return guess;

        cin.ignore(32676, '\n');
    }
}

void print_rules()
{
    cout << "Let's play a game. "
         << "I'm thinking of a number between ("
         << LOW << "-" << HIGH
         << "). You have "
         << ATTEMPTS_LIMIT << " attempts to guess what it is.\n";
}

int generate_random_int(int low, int high)
{
    // Initialize with a random seed based on the clock
    static std::mt19937 mersenne(static_cast<std::mt19937::result_type>(std::time(nullptr)));
    // Create a reusable random generator
    std::uniform_int_distribution<> random(low, high);
    return random(mersenne);
}
