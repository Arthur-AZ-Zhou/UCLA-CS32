// #include <iostream>
// #include <string>
// #include <queue>
// using namespace std;

// class Coord {
//     public:
//         Coord(int r, int c) : m_row(r), m_col(c) {
//         }
//         int r() const {
//             return m_row;
//         }
//         int c() const {
//             return m_col; 
//         }

//     private:
//         int m_row;
//         int m_col;
// };

// bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
//     queue <Coord> coordQueue;

//     Coord start(sr, sc);
//     coordQueue.push(start);
//     maze[sr][sc] = '@';

//     while (!coordQueue.empty()) { 
//         Coord coord = coordQueue.front();
//         coordQueue.pop();
//         // cout << "(" << coord.r() << ", " << coord.c() << ")" << endl;

//         if (coord.r() == er && coord.c() == ec) {
//             return true;
//         }

//         if (maze[coord.r()][coord.c() + 1] != 'X' && maze[coord.r()][coord.c() + 1] != '@') { //EAST
//             Coord c(coord.r(), coord.c() + 1);
//             coordQueue.push(c);
//             maze[coord.r()][coord.c() + 1] = '@';
//         }
//         if (maze[coord.r() - 1][coord.c()] != 'X' && maze[coord.r() - 1][coord.c()] != '@') { //NORTH
//             Coord c(coord.r() - 1, coord.c());
//             coordQueue.push(c);
//             maze[coord.r() - 1][coord.c()] = '@';
//         }
//         if (maze[coord.r()][coord.c() - 1] != 'X' && maze[coord.r()][coord.c() - 1] != '@') { //WEST
//             Coord c(coord.r(), coord.c() - 1);
//             coordQueue.push(c);
//             maze[coord.r()][coord.c() - 1] = '@';
//         }
//         if (maze[coord.r() + 1][coord.c()] != 'X' && maze[coord.r() + 1][coord.c()] != '@') { //SOUTH
//             Coord c(coord.r() + 1, coord.c());
//             coordQueue.push(c);
//             maze[coord.r() + 1][coord.c()] = '@';
//         }
//     }

//     return false;
// }

// int main() {
//     string maze[10] = {
//         "XXXXXXXXXX",
//         "X..X...X.X",
//         "X.XXXX.X.X",
//         "X.X.X..X.X",
//         "X...X.XX.X",
//         "XXX......X",
//         "X.X.XXXX.X",
//         "X.XXX....X",
//         "X...X..X.X",
//         "XXXXXXXXXX"
//     };

//     if (pathExists(maze, 10,10, 5,3, 8,8))
//         cout << "Solvable!" << endl;
//     else
//         cout << "Out of luck!" << endl;
// }