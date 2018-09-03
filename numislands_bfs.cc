#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

// Number of Islands
// Given a 2d grid map of '1's (land) and '0's (water), count the number of islands.
// An island is surrounded by water and is formed by connecting adjacent lands
// horizontally or vertically.

// You may assume all four edges of the grid are all surrounded by water.

// Example 1:
//   11110
//   11010
//   11000
//   00000
// Answer: 1

// Example 2:
//   11000
//   11000
//   00100
//   00011
// Answer: 3

// Solution:
//   Apply BFS for all the connected 1's in the grid.
//   Number of BFS runs constitutes the number of islands present in the grid.

int numislands_bfs(vector<vector<char>> & grid) {

  int row;
  int col;
  int island = 0;
  queue<int> q_row;
  queue<int> q_col;

  if(grid.empty()) return 0;
  row = grid.size();
  col = grid[0].size();

  vector<vector<bool>> visited(row, vector<bool>(col, false));

  // Invalid input
  if(!row || !col) return 0;

  cout << "Processing input of size: " << row << " x " << col << endl;
  for (int i=0; i < row; ++i) {
    for(int j=0; j<col; ++j) {

      if(grid[i][j] == '0') continue;
      if(visited[i][j]) continue;

      q_row.push(i);
      q_col.push(j);
      visited[i][j] = true;
      while(!q_row.empty()) {
        int ii = q_row.front();
        int jj = q_col.front();

        cout << "Analysing: " << ii << " " << jj << endl;

        if(ii+1<row && grid[ii+1][jj] == '1' && !visited[ii+1][jj]) {
          q_row.push(ii+1);
          q_col.push(jj);
          visited[ii+1][jj] = true;
        }

        if(jj+1<col && grid[ii][jj+1] == '1' && !visited[ii][jj+1]) {
          q_row.push(ii);
          q_col.push(jj+1);
          visited[ii][jj+1] = true;
        }

        if(ii-1>=0 && grid[ii-1][jj] == '1' && !visited[ii-1][jj]) {
          q_row.push(ii-1);
          q_col.push(jj);
          visited[ii-1][jj] = true;
        }

        if(jj-1>=0 && grid[ii][jj-1] == '1' && !visited[ii][jj-1]) {
          q_row.push(ii);
          q_col.push(jj-1);
          visited[ii][jj-1] = true;
        }

        q_row.pop();
        q_col.pop();

      }
      island++;
      cout << "Found an island: " << island << endl;
    }
  }

  return island;
}

void dfs(vector<vector<char>> & grid, int x, int y, vector<vector<bool>> & visited) {
  // if out of bounds or at a cell with '0' or '*', simply stop and return | end the dfs
  if(x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() ||
     grid[x][y] != '1' || visited[x][y]) {
    cout << "return (" << x << ", " << y << ")" << endl;
    return;
  }

  cout << "Analysing: (" << x << ", " << y << ")"<< endl;
  visited[x][y] = true;

  // Call to all neighbors
  dfs(grid, x + 1, y, visited);
  dfs(grid, x - 1, y, visited);
  dfs(grid, x, y + 1, visited);
  dfs(grid, x, y - 1, visited);
}

int numislands_dfs(vector<vector<char>> & grid) {
  int row;
  int col;
  int island = 0;

  if(grid.empty()) return 0;
  row = grid.size();
  col = grid[0].size();

  vector<vector<bool>> visited(row, vector<bool>(col, false));

  for (int i=0; i < row; ++i) {
    for(int j=0; j<col; ++j) {
      if(grid[i][j] == '1') {
        if(visited[i][j]) continue;

        cout << "Found an island at: (" << i << ", " << j << ")" << endl;
        island++;
        dfs(grid, i, j, visited);
      }
    }
  }

  return island;
}

int main(int argc, char *argv[])
{
  vector<vector<char>> grid = {
    {'1','1','1','1','0'},
    {'1','1','0','1','0'},
    {'1','1','0','0','0'},
    {'0','0','0','0','0'}
  };

  cout << "Input: " << endl;
  for (auto i = 0; i < grid.size(); ++i) {
    for (auto j = 0; j < grid[0].size(); ++j) {
      cout << grid[i][j] << " ";
    }
    cout << endl;
  }

  int num_islands = numislands_bfs(grid);

  cout << "Number of islands(BFS): " << num_islands << endl;

  num_islands = numislands_dfs(grid);

  cout << "Number of islands(DFS): " << num_islands << endl;

  vector<vector<char>> grid1 = {
    {'1','1','0','0','0'},
    {'1','1','0','0','0'},
    {'0','0','1','0','0'},
    {'0','0','0','1','1'}
  };

  cout << "Input: " << endl;
  for (auto i = 0; i < grid1.size(); ++i) {
    for (auto j = 0; j < grid1[0].size(); ++j) {
      cout << grid1[i][j] << " ";
    }
    cout << endl;
  }

  num_islands = numislands_bfs(grid1);

  cout << "Number of islands(BFS): " << num_islands << endl;

  num_islands = numislands_dfs(grid1);

  cout << "Number of islands(DFS): " << num_islands << endl;


  return 0;
}
