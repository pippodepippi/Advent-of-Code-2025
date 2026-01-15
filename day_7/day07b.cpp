#include <iostream>
#include <queue>
#include <vector>
#include <string>

#include "../utils/utils.h"

long long dfs(
    const std::vector<std::string>& grid,
    int r, int c,
    int rows, int cols,
    std::vector<std::vector<long long>>& memo
) {
    if (r < 0 || r >= rows || c < 0 || c >= cols)
        return 0;

    if (r == rows - 1)
        return 1;

    long long& res = memo[r][c];
    if (res != -1)
        return res;

    char cell = grid[r][c];
    res = 0;
    
    if (cell == '.' || cell == 'S') {
        res += dfs(grid, r + 1, c, rows, cols, memo);
    } else if (cell == '^') {
        res += dfs(grid, r, c - 1, rows, cols, memo);
        res += dfs(grid, r, c + 1, rows, cols, memo);
    }

    return res;
}


int main(int argc, char* argv[])
{
    try {
        const std::string input = getInputPath(argc, argv, "day07_input");
        std::ifstream file = openFile(input);
        
        std::vector<std::string> grid;
        std::string line;
        while (getline(file, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            grid.push_back(line);
        }

        int rows = grid.size();
        if (rows == 0) return 0;
        int cols = grid[0].size();

        int start_r = -1, start_c = -1;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == 'S') {
                    start_r = r;
                    start_c = c;
                    break;
                }
            }
            if (start_r != -1) break;
        }

        if (start_r == -1) {
            std::cerr << "Start position 'S' not found!\n";
            return 1;
        }

        std::vector<std::vector<long long>> memo(rows, std::vector<long long>(cols, -1));
        long long pathCount = dfs(grid, start_r, start_c, rows, cols, memo);

        std::cout << "Total possible paths: " << pathCount << std::endl;
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "EXCEPTION: [" << e.what() << "]\n";
        return 1;
    }
}
