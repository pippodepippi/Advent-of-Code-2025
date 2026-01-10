#include <iostream>
#include <string>
#include "../utils/utils.h"


int main(int argc, char** argv)
{
    std::string input = getInputPath(argc, argv,"day01_input");

    try {
        std::ifstream file = openFile(input);
        
        int position = 50;
        int count = 0;
        std::string line;
        
        while (std::getline(file, line)) {
            const int value = std::stoi(line.substr(1, line.size() - 1)) % 100;
            if (line[0] == 'R') {
                position += value;
            } else {
                position -= value;
            }
            position %= 100;

            if (position == 0) count++;
        }
        std::cout << "Landings on 0: " << count << '\n';
        return 0;
    }

    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}