#include "Game.h"
#include "utils.h"

Game::Game(int hole_count, int stone_count, Player whoami) {
    if (hole_count == 0 || stone_count == 0) {
        cout << "GameDeclarationError: hole_count or stone_count can not be 0" << endl;
        exit(1);
    }

    this->hole_count = hole_count;
    this->stone_count = stone_count;
    this->player = whoami;
    this->opponent = whoami == LEFT ? RIGHT : LEFT;
    vector<int> leftHole(hole_count, stone_count);
    vector<int> rightHole(hole_count, stone_count);

    leftHole.push_back(0);
    rightHole.push_back(0);

    this->gameBoard = vector<vector<int>>({
        leftHole,          // Player.LEFT
        rightHole          // Player.RIGHT
    });

    this->current_player = LEFT;
}

Game::~Game() {
}

void Game::walk() {
    if (this->current_player != this->player) {
        return;
    }

    auto board = this->gameBoard;
    this->gameBoard = this->_analyze(_Analyze_data(board, this->player, 0), 0);
    this->current_player = this->opponent;
}

vector<vector<int>> Game::_analyze(_Analyze_data analyze_data, int depth) {
#ifndef MAX_DEPTH
    cout << "Error: MAX_DEPTH NOT DEFINED" << endl;
    exit(1);
#endif
    if (depth > MAX_DEPTH) {
        this->current_player = analyze_data.whoami;
        return _move(analyze_data.board, analyze_data.whoami, analyze_data.pointY, 0, 0);
    }

    int max_state = 0, min_state = INT_MAX;
    int movement = 0;

    for (int i = 0; i < this->hole_count; i++) {
        if (analyze_data.board[analyze_data.whoami][i] == 0)
            continue;
        auto temp_board = analyze_data.board;
        this->current_player = analyze_data.whoami;
        temp_board = this->_analyze(
            _Analyze_data(
                _move(temp_board, analyze_data.whoami, i, 0, 0),
                analyze_data.whoami == this->player ? this->opponent : this->player,
                i),
            depth + 1);

        // player point and opponent point
        int pp = temp_board[this->player][this->hole_count], op = temp_board[this->opponent][this->hole_count];

        if (pp > max_state && op <= min_state) {
            max_state = pp;
            min_state = op;

            movement = i;
        } else if (op < min_state && max_state - min_state - op) {
            max_state = pp;
            min_state = op;

            movement = i;
        }
    }

    if (depth == 0)
        cout << "MOVE: " << movement << "\n";

    this->current_player = analyze_data.whoami;
    analyze_data.board = _move(analyze_data.board, analyze_data.whoami, movement, 0, 0);
    return analyze_data.board;
}

vector<vector<int>> Game::_move(vector<vector<int>> board, int pointX, int pointY, int len, int depth) {
    if (depth == 0) {
        len = board[pointX][pointY];
        board[pointX][pointY] = 0;

        return _move(board, pointX, pointX == 0 ? pointY + 1 : pointY - 1, len, depth + 1);
    }

    if (len == 0) {
        return board;
    }

    bool isN1 = false;

    // if `not in board` or `not in player hole`
    if (pointY > this->hole_count || (pointY == this->hole_count && pointX != this->current_player)) {
        pointY = pointX == 0 ? this->hole_count - 1 : 0;
        pointX = ++pointX % 2;
    }

    if (pointY < 0) {
        if (pointX == this->current_player) {
            isN1 = true;
            pointY = this->hole_count;
        } else {
            pointX = 0;
            pointY = 0;
        }
    }

    if ((len == 1 && board[pointX][pointY] == 0) ||
        (len == 1 && pointX == this->current_player && pointY == this->hole_count)) {
        len--;
        board[pointX][pointY]++;
        return board;
    } else if (len == 1) {
        len += board[pointX][pointY];
        board[pointX][pointY] = 0;
    } else {
        len--;
        board[pointX][pointY]++;
    }

    if (isN1) {
        pointX = 0;
        pointY = -1;
    }

    return _move(board, pointX, pointX == 0 ? pointY + 1 : pointY - 1, len, depth + 1);
}

void Game::move(int hole) {
    if (this->current_player != this->opponent) {
        return;
    }

    if (hole >= this->hole_count || hole < 0) {
        cout << "GameMovementError: You make an illegal move" << endl;
        exit(1);
    }

    this->gameBoard = _move(this->gameBoard, this->opponent, hole, 0, 0);
    this->current_player = this->player;
}

bool Game::end() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < this->hole_count; j++) {
            if (this->gameBoard[i][j] != 0)
                return false;
        }
    }

    return true;
}