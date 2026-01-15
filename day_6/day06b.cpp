#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#include "../utils/utils.h"

int main(int argc, char* argv[]) {
    try{
        const std::string input = getInputPath(argc, argv, "day06_input");
        std::ifstream file = openFile(input);

        std::vector<std::string> parsed_input;
        std::string line;
        std::size_t longest_size = 0;

        // Read grid lines
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            if (line[0] == '+' || line[0] == '-' || line[0] == '*' || line[0] == '/') break;
            for (auto& c : line) if (c == ' ') c = '.';
            longest_size = std::max(longest_size, line.size());
            parsed_input.push_back(line);
        }

        const std::string& signs = line;

        // Ensure all rows are same length
        for (auto& row : parsed_input) row.append(longest_size - row.size(), '.');

        // Identify start indices of columns
        std::vector<std::size_t> start_indices;
        std::size_t start = 0;
        while (start < signs.size()) {
            start_indices.push_back(start);
            start = signs.find_first_not_of(' ', start + 1);
            if (start == std::string::npos) break;
        }
        start_indices.push_back(longest_size); // add sentinel

        std::size_t total = 0;

        for (std::size_t i = 0; i < start_indices.size() - 1; i++) {
            std::size_t col_start = start_indices[i];
            std::size_t col_end = start_indices[i + 1];
            char sign = signs[col_start];

            std::size_t ans = (sign == '*') ? 1 : 0;

            for (std::size_t col = col_start; col < col_end; col++) {
                std::string num_str;
                for (const auto& row : parsed_input) {
                    if (row[col] != '.') num_str += row[col];
                }
                if (!num_str.empty()) {
                    std::size_t val = std::stoull(num_str);
                    if (sign == '+') ans += val;
                    else if (sign == '*') ans *= val;
                }
            }
            total += ans;
        }

        std::cout << total << '\n';
    }
    catch (const std::exception& e) {
        std::cerr << "EXCEPTION: [" << e.what() << '\n';
        return 1;
    } 
}
