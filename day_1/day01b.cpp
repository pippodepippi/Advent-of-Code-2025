#include <iostream>
#include <string>
#include "../utils/utils.h"


int main(int argc, char* argv[])
{
    std::string input = "../input/day01_input";
    if (argc > 1) {
        input = argv[1];
    }

    try {
        std::ifstream file = openFile(input);
        
        long long curr = 50;
        long long count = 0;
        std::string line;
        
        while (std::getline(file, line)) {
            
            long long num = std::stoll(line.substr(1, line.size() - 1));

            if (line[0] == 'L') {
                int cost = (curr == 0 ? 100 : curr);
                if ( num >= cost ) {
                    count ++;
                    num -= cost;
                    curr = ((-num % 100) + 100) % 100;
                    count += num / 100;
                } else {
                    curr = (curr - num + 100) % 100;
                }
            } else {
                int next = (curr + num) % 100;
                int rest = 100 - curr;

                if (num >= rest) {
                    count++;
                    num -= rest;
                    count += num / 100;
                }
                curr = next;
            }
        }
        std::cout << "0 crossings: " << count << '\n';
        return 0;
    }

    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}