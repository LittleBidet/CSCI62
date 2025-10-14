#include <vector>
#include <stack>
#include <utility>
using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }
        vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
        int islandCount = 0;
        for(int i = 0; i < grid.size(); i++){
            for(int j = 0; j < grid[i].size(); j++){
                if (grid[i][j] == '1' && !visited[i][j]) {
                    islandCount++;
                    islandHelper(i, j, visited, grid);
                }
            }
        }
        return islandCount;
    }
    void islandHelper(int x, int y, vector<vector<bool>>& visited, vector<vector<char>>& grid){
        int numRows = grid.size();
        int numCols = grid[0].size();

        stack<pair<int, int>> stack;
        stack.push({x, y});
        visited[x][y] = true;

        while(!stack.empty()){
            std::pair<int, int> current = stack.top();
            stack.pop();
            int m = current.first;
            int n = current.second;

            //Above
            if (m - 1 >= 0 && grid[m - 1][n] == '1' && !visited[m - 1][n]) {
                visited[m - 1][n] = true;
                stack.push({m - 1, n});
            }

            //Below
            if (m + 1 < numRows && grid[m + 1][n] == '1' && !visited[m + 1][n]) {
                visited[m + 1][n] = true;
                stack.push({m + 1, n});
            }

            //Left
            if (n - 1 >= 0 && grid[m][n - 1] == '1' && !visited[m][n - 1]) {
                visited[m][n - 1] = true;
                stack.push({m, n - 1});
            }

            //Right
            if (n + 1 < numCols && grid[m][n + 1] == '1' && !visited[m][n + 1]) {
                visited[m][n + 1] = true;
                stack.push({m, n + 1});
            }
        }
    }
};