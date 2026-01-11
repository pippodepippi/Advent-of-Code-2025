#include <iostream>
#include <string>
#include "../utils/utils.h"


int main(int argc, char** argv)
{

    try {
        std::string input = getInputPath(argc, argv, "day03_input");
        std::ifstream file = openFile(input);

        std::string line;
        int total_joltage = 0;

        while (std::getline(file, line)) {
            int max1 = -1;
            int max2 = -1;

            for (char c : line) {
                const int digit = c - '0';

                if (digit > max1) {
                    max2 = max1;
                    max1 = digit;
                }
                else if (digit > max2) {
                    max2 = digit;
                }
            }

            total_joltage += max1 * 10 + max2;
        }

        std::cout << total_joltage << '\n';
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}