#include <array>
#include <deque>
#include <iostream>
#include <string>
#include <vector>
#include "../utils/utils.h"

struct Grid {
    std::vector<char> data;
    int rows = 0;
    int cols = 0;
};

Grid loadFlattenedGrid(const std::string& path) {
    std::ifstream file = openFile(path);

    std::vector<std::string> lines;
    std::string line;
    size_t maxWidth = 0;

    while(std::getline(file, line)) {
        if (line.empty()) continue;
        maxWidth = std::max(maxWidth, line.length());
        lines.push_back(line);
    }

    int cols = static_cast<int>(maxWidth + 2);
    int rows = static_cast<int>(lines.size() + 2);

    std::vector<char> flatGrid(rows * cols, ' ');

    for (int i = 0; i < lines.size(); ++i) {
        size_t startIdx = (i + 1) * cols + 1;
        std::copy(lines[i].begin(), lines[i].end(), flatGrid.begin() + startIdx);
    }

    return {std::move(flatGrid), rows, cols };
}

int count_neighbours(const std::vector<char>& grid, int rows, int cols) {
    // We work on a copy to keep the original logic intact
    std::vector<char> mat = grid;
    std::vector<uint8_t> neighbours(rows * cols, 0);
    std::vector<int> stack;
    stack.reserve(rows * cols / 4); // Heuristic reservation

    // Pre-calculate strides
    const int stride = cols;

    // Initial pass: Count neighbours and find initial candidates
    // We skip the padding borders (1 to rows-1)
    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < cols - 1; ++j) {
            int idx = i * stride + j;
            if (mat[idx] != '@') continue;

            uint8_t n = 0;
            // Unrolled/Direct 1D neighbor checks
            if (mat[idx - stride - 1] == '@') n++;
            if (mat[idx - stride]     == '@') n++;
            if (mat[idx - stride + 1] == '@') n++;
            if (mat[idx - 1]          == '@') n++;
            if (mat[idx + 1]          == '@') n++;
            if (mat[idx + stride - 1] == '@') n++;
            if (mat[idx + stride]     == '@') n++;
            if (mat[idx + stride + 1] == '@') n++;

            neighbours[idx] = n;
            if (n < 4) {
                stack.push_back(idx);
            }
        }
    }

    int replaced = 0;
    const int off[8] = { -stride-1, -stride, -stride+1, -1, 1, stride-1, stride, stride+1 };

    while (!stack.empty()) {
        int idx = stack.back();
        stack.pop_back();

        // Safety check: only process if it's still '@' and below threshold
        if (mat[idx] != '@' || neighbours[idx] >= 4) continue;

        mat[idx] = '.';
        replaced++;

        // Update neighbors
        for (int i = 0; i < 8; ++i) {
            int n_idx = idx + off[i];
            if (mat[n_idx] == '@') {
                if (--neighbours[n_idx] == 3) {
                    stack.push_back(n_idx);
                }
            }
        }
    }

    return replaced;
}

int main(int argc, char* argv[])
{

try {
        std::string input = getInputPath(argc, argv, "day04_input");
        
        Grid grid = loadFlattenedGrid(input);

        int result = count_neighbours(grid.data, grid.rows, grid.cols);
        std::cout << result << std::endl;

        return 0;

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}