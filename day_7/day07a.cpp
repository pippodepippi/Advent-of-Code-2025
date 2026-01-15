#include <iostream>
#include <queue>
#include <vector>
#include <string>

#include "../utils/utils.h"

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


        std::queue<std::pair<int,int>> q;
        q.push({start_r, start_c});
        std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols,false));
        int split_cnt = 0;

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            if (r < 0 || r >= rows || c < 0 || c >= cols) continue;
            if (visited[r][c]) continue;

            visited[r][c] = true;
            char cell = grid[r][c];

            if (cell == '.') {
                // move down
                if (r + 1 < rows) q.push({r + 1, c});
            } else if (cell == '^') {
                split_cnt++;
                // push left and right if in bounds
                if (c - 1 >= 0) q.push({r, c - 1});
                if (c + 1 < cols) q.push({r, c + 1});
            } else if (cell == 'S') {
                // move down from start
                if (r + 1 < rows) q.push({r + 1, c});
            }
        }

        std::cout << "Total splits: " << split_cnt << std::endl;
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "EXCEPTION: [" << e.what() << "]\n";
        return 1;
    }
}
