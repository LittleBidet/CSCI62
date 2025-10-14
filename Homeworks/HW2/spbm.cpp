#include <vector>
#include <queue>

class Solution {
public:
    int shortestPathBinaryMatrix(std::vector<std::vector<int>>& grid) {
        int n = grid.size();
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1) {
            return -1;
        }
        if (n == 1) {
            return 1;
        }
        std::queue<std::vector<int>> q;
        q.push({0, 0, 1});
        grid[0][0] = 1;

        while (!q.empty()) {
            std::vector<int> current = q.front();
            q.pop();
            int r = current[0];
            int c = current[1];
            int length = current[2];

            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    if (i == 0 && j == 0) {
                        continue;
                    }
                    int new_r = r + i;
                    int new_c = c + j;

                    if (new_r == n - 1 && new_c == n - 1) {
                        return length + 1;
                    }

                    if (new_r >= 0 && new_r < n && new_c >= 0 && new_c < n && grid[new_r][new_c] == 0) {
                        grid[new_r][new_c] = 1;
                        q.push({new_r, new_c, length + 1});
                    }
                }
            }
        }
        return -1;
    }
};