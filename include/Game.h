#pragma once

#include <iostream>
#include <vector>
using namespace std;

#ifndef MAX_DEPTH
#define MAX_DEPTH 5
#endif

enum Player {
    LEFT = 0,
    RIGHT = 1
};

typedef struct _Analyze_data {
    vector<vector<int>> board;
    Player whoami;
    int pointY;
    _Analyze_data(vector<vector<int>> board, Player whoami, int pointY) : board(board), whoami(whoami), pointY(pointY){};
} _Analyze_data;

class Game {
  private:
    int hole_count;
    int stone_count;
    Player player;
    Player opponent;

    vector<vector<int>> _analyze(_Analyze_data analyze_data, int depth);
    vector<vector<int>> _move(vector<vector<int>> board, int pointX, int pointY, int len, int depth);

  public:
    vector<vector<int>> gameBoard;
    Player current_player;
    Game(int hole_count, int stone_count, Player whoami);

    void walk();
    void move(int hole);
    bool end();

    ~Game();
};