#include <iostream>
#include <vector>
#include <array>

using namespace std;

typedef enum {BLACK, WHITE} Color ;

class Coordinate
{
public:
    bool operator== (const Coordinate & that) const
    {
        return (x == that.x && y == that.y);
    }

    friend ostream& operator<< (ostream & out, Coordinate & t)
    {
        out << "[" << t.x << ", " << t.y << "]";
        return out;
    }

    int x, y;
};

#if 0
bool PathElementIsFeasible(const vector<vector<Color>>& maze,
                           const Coordinate& prev, const Coordinate& cur) {
    if (!(0 <= cur.x && cur.x < maze.size() && 0 <= cur.y &&
          cur.y < maze[cur.x].size() && maze[cur.x][cur.y] == WHITE)) {
        return false;
    }
    return cur == Coordinate{prev.x + 1, prev.y} ||
                                cur == Coordinate{prev.x - 1, prev.y} ||
                                cur == Coordinate{prev.x, prev.y + 1} ||
                                cur == Coordinate{prev.x, prev.y - 1};
}

// Perform DFS to find a feasible path.
bool SearchMazeHelper(const Coordinate& cur, const Coordinate& e,
                      vector<vector<Color>>* maze_ptr,
                      vector<Coordinate>* path_ptr) {
  auto& maze = *maze_ptr;
  // Checks cur is within maze and is a white pixel.
  if (cur.x < 0 || cur.x >= maze.size() || cur.y < 0 ||
      cur.y >= maze[cur.x].size() || maze[cur.x][cur.y] != WHITE) {
    return false;
  }
  auto& path = *path_ptr;
  path.emplace_back(cur);
  maze[cur.x][cur.y] = BLACK;
  if (cur == e) {
    return true;
  }

  for (const Coordinate& next_move :
       {Coordinate{cur.x, cur.y + 1}, Coordinate{cur.x, cur.y - 1},
        Coordinate{cur.x + 1, cur.y}, Coordinate{cur.x - 1, cur.y}}) {
    if (SearchMazeHelper(next_move, e, maze_ptr, path_ptr)) {
      return true;
    }
  }
  // Cannot find a path, remove the entry added in path.emplace_back(cur).
  path.pop_back();
  return false;
}

vector<Coordinate> SearchMaze(vector<vector<Color>> maze, const Coordinate& s,
                              const Coordinate& e) {
    vector<Coordinate> path;
    SearchMazeHelper(s, e, &maze, &path);
    return path;
}
#endif

bool isValidMove(Coordinate & n, vector<vector<Color>> & maze)
{
    return (n.x >= 0 && n.x < maze.size() &&
            n.y >= 0 && n.y < maze[n.x].size() &&
            maze[n.x][n.y] == WHITE);
}

bool SearchMazeHelper(Coordinate & cur, Coordinate & e, vector<vector<Color>>*  maze,
                      vector<Coordinate>* path)
{
    if(cur == e) return true;

    //Array of moves
    const array<array<int, 2>, 4> kshift = {
        {
            {0,1},
            {0,-1},
            {1,0},
            {-1, 0}
        }
    };

    // move forward on every move till you find E,
    // if we hit a invalid move then pop and explore the previous unvisited node.
    for (const array<int, 2> & s : kshift) {
        Coordinate next{cur.x + s[0], cur.y + s[1]};
        cout << "Try move: " << next << endl;
        if(isValidMove(next, *maze)) {
            (*maze)[next.x][next.y] = BLACK;
            cout << "Valid move: " << next << endl;
            path->emplace_back(next);
            cout << "Path: " ;
            for (auto it = path->begin(); it != path->end(); ++it) {
                cout << *it << ", ";
            }
            cout << endl;

            // Move ahead with the next node, DFS style
            cout << "Explore: " << next << endl;
            if(SearchMazeHelper(next, e, maze, path)) {
                return true;
            }
            cout << "Pop " << path->back() << endl;;
            path->pop_back();
        }
    }

    return false;
}

vector<Coordinate> SearchMaze(vector<vector<Color>> maze, Coordinate & s,
                              Coordinate & e)
{
    vector<Coordinate> path;

    // Mark source node with black to avoid being reconsidered
    maze[s.x][s.y] = BLACK;
    cout << "Mark [" << s.x << ", "<< s.y << "] " << " with BLACK" << endl;

    // Add s to path
    path.emplace_back(s);
    cout << "Path: " ;
    for (auto it = path.begin(); it != path.end(); ++it) {
        cout << *it << ", ";
    }
    cout << endl;

    if(!SearchMazeHelper(s, e, &maze, &path))
    {
        // No valid move exist then pop the source so that path vector is empty
        path.pop_back();
    }

    return path;
}

int main(int argc, char *argv[])
{
    vector<vector<Color>> maze = {
        {BLACK, WHITE, BLACK, BLACK, WHITE},
        {WHITE, WHITE, WHITE, WHITE, WHITE},
        {WHITE, BLACK, WHITE, BLACK, WHITE},
        {WHITE, WHITE, BLACK, WHITE, WHITE},
        {WHITE, WHITE, WHITE, BLACK, WHITE},
    };

    cout << "Input Maze: \n" ;
    for (int i = 0; i < maze.size(); ++i) {
        for (int j = 0; j < maze[i].size(); ++j) {
            if(maze[i][j] == BLACK)
                cout << "B" << " ";
            else
                cout << "W" << " ";
        }
        cout << endl;
    }
    cout << endl;

    Coordinate s{4,0};
    Coordinate e{0,4};

    vector<Coordinate> path = SearchMaze(maze, s, e);

    cout << "Result Maze: \n" ;
    for (int i = 0; i < maze.size(); ++i) {
        for (int j = 0; j < maze[i].size(); ++j) {
            if(maze[i][j] == BLACK)
                cout << "B" << " ";
            else
                cout << "W" << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Result Path: " ;
    for (auto it = path.begin(); it != path.end(); ++it) {
        cout << *it << ", ";
    }
    cout << endl;
    return 0;
}
