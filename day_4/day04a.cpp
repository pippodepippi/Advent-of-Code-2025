#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "../utils/utils.h"

static constexpr std::array<std::array<int, 2>, 8> OFFSETS {{
    {{-1,-1}}, {{-1,0}}, {{-1,1}},
    {{ 0,-1}},           {{ 0,1}},
    {{ 1,-1}}, {{ 1,0}}, {{ 1,1}}
}};


int count_neighbours(const std::vector<std::string>& mat) {
    const int rows = static_cast<int>(mat.size());
    const int cols = static_cast<int>(mat[0].size());
    int count = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (mat[i][j] != '@')
                continue;
            
            int neighbors = 0;

            for (const auto& o : OFFSETS) {
                neighbors += (mat[i + o[0]][j + o[1]] == '@');
            }

            count += (neighbors < 4);
        }
    }

    return count;
}

int main(int argc, char* argv[])
{

try {
        std::string input = getInputPath(argc, argv, "day04_input");
        std::ifstream file = openFile(input);

        std::vector<std::string> matrix;
        std::string line;

        while (std::getline(file, line)) {
            if (!line.empty())
            matrix.push_back(" " + line + " ");
        }

        const std::string border(matrix[0].size(), ' ');
        matrix.insert(matrix.begin(), border);
        matrix.push_back(border);


        int result = count_neighbours(matrix);
        std::cout << result << std::endl;

        return 0;

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}