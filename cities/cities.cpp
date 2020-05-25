#include <cctype>
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>

#define CITIES_CSV "worldcities.csv"

using namespace std;

enum e_PlaysFirst {
    USER, AI,
};

e_PlaysFirst get_who_plays_first(int argc, char *argv[]);

vector<string> load_cities(string csv_fname);
string strip(string &city_name, char symbol);

void user_says_city(vector<string> &cities, string &cur_city);
void ai_says_city(vector<string> &cities, string &cur_city);

string get_user_city();
bool validate_user_city(vector<string> &cities, string &cur_city, string &user_city);
int city_exists(vector<string> &cities, string &city);

void remove_city(vector<string> &cities, int city_index);
void lower(string &city);
void print_ai_city(string city);

string get_ai_city();

int pick_random_number(int min, int max);
void usage_error();

int main(int argc, char** argv)
{
    e_PlaysFirst plays_first = get_who_plays_first(argc, argv);
    vector<string> cities = load_cities(CITIES_CSV);
    string cur_city = "";

    for (;;) {
        if (plays_first == USER) {
            user_says_city(cities, cur_city);
            ai_says_city(cities, cur_city);
        } else {
            ai_says_city(cities, cur_city);
            user_says_city(cities, cur_city);
        }
    }

    return 0;
}

void ai_says_city(vector<string> &cities, string &cur_city)
{
    if (cur_city == "") { // AI First starts the game
        int city_index = pick_random_number(0, cities.size());
        print_ai_city(cities[city_index]);
        cur_city = cities[city_index];
        cities.erase(cities.begin() + city_index);
        return;
    } else { // AI plays after user
        char last_letter = cur_city[cur_city.length()-1];
        for (int city_index = 0; city_index < cities.size(); ++city_index) {
            if (cities[city_index][0] == last_letter) {
                print_ai_city(cities[city_index]);
                cur_city = cities[city_index];
                cities.erase(cities.begin() + city_index);
                return;
            }
        }
    }
}

void print_ai_city(string city)
{
    city[0] = toupper(city[0]);
    cout << "AI's city: " << city << '\n';
}

void user_says_city(vector<string> &cities, string &cur_city)
{
    while (true) {
        string user_city = get_user_city();
        if (validate_user_city(cities, cur_city, user_city)) {
            cur_city = user_city;
            return;
        }
    }
}

/*
 * Checks whether city exists in the game cities csv file.
 * Returns city's index if exists otherwise -1.
 */
int city_exists(vector<string> &cities, string &city)
{
    for (int city_index = 0; city_index < cities.size(); ++city_index) {
        if (cities[city_index] == city)
            return city_index;
    }
    return -1;
}

/*
 * Deletes pciekd city from cities vector.
 */
void remove_city(vector<string> &cities, int city_index)
{
    cities.erase(cities.begin() + city_index);
}

bool validate_user_city(vector<string> &cities, string &cur_city, string &user_city)
{
    if (cur_city == "") {
        int city_index = city_exists(cities, user_city);
        if (city_index != -1) {
            remove_city(cities, city_index);
            return true;
        } else {
            cerr << "This city doesn't exist." << '\n';
            return false;
        }
    } else {
        // Check if user's city name first letter is equal to current city's last letter
        char cur_city_last_letter = cur_city[cur_city.length()-1];
        if (user_city[0] != cur_city_last_letter) {
            cerr << "City's name must start with " <<
                         static_cast<char>(toupper(cur_city_last_letter)) << '\n';
            return false;
        }
        else {
            int city_index = city_exists(cities, user_city);
            if (city_index != -1) {
                cerr << cities[city_index] << " Exists" << '\n';
                remove_city(cities, city_index);
                return true;
            } else {
                cerr << "This city doesn't exist." << '\n';
                return false;
            }
        }
    }
}

string get_user_city()
{
    string user_city;
    for (;;) {
        cout << "Your city: ";
        getline(cin, user_city);
        if (cin.fail()) {
            cerr << "Invalid input" << endl;
            cin.clear();
            cin.ignore(32767, '\n');
            continue;
        }
        lower(user_city); // Because cities in the game are in the lower case
        return user_city;
    }
}

void lower(string &city)
{
    for (int i = 0; i < city.length(); ++i)
        city[i] = tolower(city[i]);
}

/*
 * Strips off "" from a city_name.
 */
string strip(string &city_name, char symbol)
{
    string city;
    for (const char ch : city_name) {
        if (ch == symbol)
            continue;
        else
            city.push_back(ch);
    }
    return city;
}

/*
 * Loads cities into vector of strings from the csv file.
 */
vector<string> load_cities(string csv_fname)
{
    constexpr int num_columns = 11;
    constexpr int city_name_column = 1;
    fstream infile;
    infile.open(csv_fname, ios::in);

    // Skip first line headers
    string line;
    getline(infile, line);

    // Read the rest of the file
    vector<string> cities;
    while (infile.good()) {
        vector<string> temp {num_columns};
        for (int column = 0; column < num_columns; ++column) {
            if (column == num_columns-1)
                getline(infile, temp[column], '\n');
            else
                getline(infile, temp[column], ',');
        }
        string city_name = strip(temp[city_name_column], '"');
        lower(city_name);
        cities.push_back(city_name);
    }

    return cities;
}

/*
 * Returns USER (0) or AI (1) specified as a command line argument.
 */
e_PlaysFirst get_who_plays_first(int argc, char *argv[])
{
    if (argc != 2)
        usage_error();

    string plays_first = argv[1];

    if (plays_first == "--user")
        return USER;
    else if (plays_first == "--ai")
        return AI;
    else
        usage_error();
}

int pick_random_number(int min, int max)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(min, max);
    auto randomInt = uni(rng);
    return randomInt;
}

/*
 * Print Usage error message to the console.
 */
void usage_error()
{
    cerr << "Usage: " << __FILE__ << " [--user|--ai]\n";
    exit(1);
}
