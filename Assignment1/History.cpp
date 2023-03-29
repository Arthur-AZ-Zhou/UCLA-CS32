#include "History.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols) {
    m_rows = nRows;
    m_cols = nCols;
}

bool History::record(int r, int c) {
    if (r <= 0  ||  c <= 0  ||  r > m_rows  ||  c > m_cols) {
        return false;
    }

    history_grid[r][c] = history_grid[r][c] + 1;

    return true;
}

void History::display() const {
    clearScreen();

    for (int r = 1; r <= m_rows; r++) {
        for (int c = 1; c <= m_cols; c++) {
            char printchar = history_grid[r][c] + 64;
            // cout << history_grid[r][c];
            if (history_grid[r][c] == 0) { //print period 
                cout << ".";
                continue;
            }
            if (history_grid[r][c] >= 26) { //26 carrots or greater
                 cout << "Z";
                continue;
            }
            cout << printchar; 
        }
        
        cout << "\n";
    }

    cout << "\n";
}
