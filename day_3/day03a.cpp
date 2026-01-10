#include <iostream>
#include <string>
#include <charconv>
#include "../utils/utils.h"


int main(int argc, char** argv)
{

    try {
        std::string input = getInputPath(argc, argv, "day03_input");
        std::ifstream file = openFile(input);

        std::string line;
        
        while (std::getline(file, line)) {
            std::cout << line << '\n';
        }
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}