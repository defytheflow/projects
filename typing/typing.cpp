// Version 1.
// A user is given a sentence.
// A prompt appears.
// User types the sentence.
// Before user started typing a timer is set.
// After user finished typing a timer is turned off.
// Number of mistakes is calculated.
// User is given a result. Mistakes, Time, and WPM.

// How to highlight a mistaker symbol with red?
// How to display time?
// The top line can keep count of mistakes, and time passed.
// Second line the sentenct.
// This line the user input.
// How to use unbuffered input?
// We need to echo the input character to the screen.

#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

constexpr const char* red = "\033[0;31m";
constexpr const char* green = "\033[1;32m";
constexpr const char* reset = "\033[0m";

void typing_loop(std::vector<int>& mistakes, const std::string& text);
void print_text(const std::string& text);
void print_mistakes(const std::vector<int>& mistakes, const std::string& text);

int main() {
    std::vector<int> mistakes;  // indices of mistyped letters.
    std::string text = "This is some text. Let's add some more text here and see if is "
                       "works correctly 12.";

    print_text(text);

    auto start = std::chrono::steady_clock::now();
    typing_loop(mistakes, text);
    auto end = std::chrono::steady_clock::now();

    print_mistakes(mistakes, text);

    auto seconds_elapsed =
        std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    double minutes_elapsed = seconds_elapsed / 60.0;
    int wpm = (text.length() / 5) / (minutes_elapsed);

    std::cout << "WPM: " << wpm << "\n";
    std::cout << "Seconds: " << seconds_elapsed << "\n";
    std::cout << "Minutes: " << minutes_elapsed << "\n";
    std::cout << "Mistakes: " << mistakes.size() << "\n";
    std::cout << "Correct: " << text.length() - mistakes.size() << "\n";
    std::cout << "Accurracy: " << (text.length() - mistakes.size()) / 100.0 << "\n";

    return 0;
}

void typing_loop(std::vector<int>& mistakes, const std::string& text) {
    const char* p_text = text.c_str();

    while (true) {
        char ch = getchar();

        if (*p_text == '\0') {
            break;
        }

        if (ch != *p_text) {
            mistakes.push_back(p_text - text.c_str());
        }

        ++p_text;
    }
}

void print_text(const std::string& text) {
    std::cout << text << "\n";
}

void print_mistakes(const std::vector<int>& mistakes, const std::string& text) {
    auto& vec = mistakes;

    for (uint32_t i = 0; i < text.length(); ++i) {
        bool is_mistake = std::find(vec.begin(), vec.end(), i) != vec.end();
        std::cout << (is_mistake ? red : green) << text[i];
    }

    std::cout << reset << "\n";
}
