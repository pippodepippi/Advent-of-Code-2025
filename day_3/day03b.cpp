#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "../utils/utils.h"

// 12 digits can fit inside a 64 bit
typedef std::uint64_t joltage_t;


int main(int argc, char* argv[])
{

try {
        std::string input = getInputPath(argc, argv, "day03_input");
        std::ifstream file = openFile(input);

        std::string line;
        joltage_t total_joltage = 0;
        const int n_digits = 12;

        while (std::getline(file, line)) {
            if (line.size() < n_digits) continue;

            joltage_t current_joltage = 0;
            auto search_start = line.begin();

            for (int i = 0; i < n_digits; ++i) {
                // Chars we must leave behind
                auto search_end = line.end() - (n_digits - i - 1);

                auto max_it = std::max_element(search_start, search_end);

                current_joltage = current_joltage * 10 + (*max_it - '0');

                search_start = max_it + 1;
            }
            total_joltage += current_joltage;
        }
 
        std::cout << total_joltage << std::endl;
        return 0;

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}