#include <iostream>
#include <string>
using namespace std;

class Coord {
    public:
        Coord(int r, int c) : m_row(r), m_col(c) {
        }
        int r() const {
            return m_row;
        }
        int c() const {
            return m_col; 
        }

    private:
        int m_row;
        int m_col;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    if (sr == er && sc == ec) {
        return true;
    }

    maze[sr][sc] = '@';

    if (maze[sr][sc + 1] != 'X' && maze[sr][sc + 1] != '@') { //EAST
        if(pathExists(maze, nRows, nCols, sr, sc + 1, er, ec)) {
            return true;
        }
    }
    if (maze[sr - 1][sc] != 'X' && maze[sr - 1][sc] != '@') { //NORTH
        if(pathExists(maze, nRows, nCols, sr - 1, sc, er, ec)) {
            return true;
        }
    }
    if (maze[sr][sc - 1] != 'X' && maze[sr][sc - 1] != '@') { //WEST
        if(pathExists(maze, nRows, nCols, sr, sc - 1, er, ec)) {
            return true;
        }
    }
    if (maze[sr + 1][sc] != 'X' && maze[sr + 1][sc] != '@') { //SOUTH
        if(pathExists(maze, nRows, nCols, sr + 1, sc, er, ec)) {
            return true;
        }
    }

    return false;
}

// int main() {
//     string maze[10] = {
//         "XXXXXXXXXX",
//         "X..X...X.X",
//         "XXXXXX.X.X",
//         "X.X.X..X.X",
//         "X...X.XX.X",
//         "XXX......X",
//         "X.X.XXXX.X",
//         "X.XXX....X",
//         "X...X..X.X",
//         "XXXXXXXXXX"
//     };

//     if (pathExists(maze, 10,10, 1,1, 8,8))
//         cout << "Solvable!" << endl;
//     else
//         cout << "Out of luck!" << endl;
// }