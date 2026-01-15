#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "../utils/utils.h"

long long applyColumngOperators(const std::vector<std::vector<long long>>& matrix,
                            const std::vector<char>& operators)
{
    if (matrix.empty())
        throw std::runtime_error("No values provided");
    
    size_t rows = matrix.size();
    size_t cols = operators.size();

    for (const auto& row : matrix) {
        if (row.size() != cols)
            throw std::runtime_error("Column count mismatch");
    }

    long long ans = 0;

    for (size_t col = 0; col < cols; ++col) {
        long long result = matrix[0][col];
        
        for (size_t row = 1; row < rows; ++row) {
            switch(operators[col]) {
                case '+': result += matrix[row][col]; break;
                case '*': result *= matrix[row][col]; break;
                case '-': result -= matrix[row][col]; break;
                case '/':
                    if (matrix[row][col] == 0)
                        throw std::runtime_error("Division by zero");
                    result /= matrix[row][col];
                    break;
                default:
                    throw std::runtime_error("Unknown operator");
            }
        }

        ans += result;
    }
    return ans;
}


int main(int argc, char* argv[])
{

try {

        const std::string input = getInputPath(argc, argv, "day06_input");
        std::ifstream file = openFile(input);

        std::vector<std::vector<long long>> matrix;
        std::vector<char> operators;

        std::string line;
        std::vector<std::string> lines;

        while (std::getline(file, line)) {
            if (!line.empty())
                lines.push_back(line);
        }

        if (lines.size() < 2) {
            std::cerr << "Not enough data\n";
            return 1;
        }

        std::stringstream opStream(lines.back());
        char op;
        while(opStream >> op) {
            operators.push_back(op);
        }

        for (size_t i = 0; i < lines.size() - 1; ++i) {
            std::istringstream iss(lines[i]);
            std::vector<long long> row;
            long long value;

            while (iss >> value) {
                row.push_back(value);
            }

            matrix.push_back(row);
            }
                    
        auto sol = applyColumngOperators(matrix, operators);

        std::cout << sol << '\n';
        
        return 0;
    }

    catch (const std::exception& e) {
        std::cerr << "EXCEPTION: [" << e.what() << '\n';
        return 1;
    }


}