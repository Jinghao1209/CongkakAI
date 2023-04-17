#include "utils.h"

void printBoard(vector<vector<int>> board) {
    for (size_t i = 0; i < board.size(); i++) {
        for (size_t j = 0; j < board[i].size(); j++) {
            if (j == board[i].size() - 1) {
                cout << "[" << board[i][j] << "] ";
                continue;
            }
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}