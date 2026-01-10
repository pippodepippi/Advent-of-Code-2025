#include <iostream>
#include <string>
#include <charconv>
#include "../utils/utils.h"

constexpr std::size_t POW10[] = {
    1ULL,
    10ULL,
    100ULL,
    1000ULL,
    10000ULL,
    100000ULL,
    1000000ULL,
    10000000ULL,
    100000000ULL,
    1000000000ULL
};

inline std::size_t digit_count(std::size_t n)
{
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    return 10;
}

bool has_repeated_pattern(std::size_t number)
{
    const std::size_t d = digit_count(number);

    for (std::size_t k = 1; k <= d / 2; ++k) {
        if (d % k != 0) continue;

        const std::size_t pow = POW10[k];
        const std::size_t pattern = number % pow;

        std::size_t n = number;
        bool ok = true;

        for (std::size_t i = 0; i < d / k; ++i) {
            if (n % pow != pattern) {
                ok = false;
                break;
            }
            n /= pow;
        }
        if (ok) return true;
    }

    return false;
}

int main(int argc, char** argv)
{

    try {
        std::string input = getInputPath(argc, argv, "day02_input");
        std::ifstream file = openFile(input);

        std::string line;
        std::getline(file, line);

        std::size_t sum = 0;
        std::size_t pos = 0;


        while (pos < line.size()) {
            const std::size_t dash = line.find('-', pos);
            std::size_t comma = line.find(',', pos);

            if (comma == std::string::npos) comma = line.size();

            std::size_t start = 0, end = 0;
            std::from_chars(line.data() + pos, line.data() + dash, start);
            std::from_chars(line.data() + dash + 1, line.data() + comma, end);

            for (std::size_t num = start; num <= end; ++num) {
                if (has_repeated_pattern(num)) {
                    sum += num;
                }
            }
            pos = comma + 1;
        }
        std::cout << sum << '\n';
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}