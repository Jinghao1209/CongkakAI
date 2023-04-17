// bash build.sh && clear && ./main.out

#define MAX_DEPTH 5          // to customize MAX_DEPTH, it must be defined before #include "Game.h"

#include "Game.h"
#include "utils.h"
#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
    Game game(5, 5, LEFT);

    while (!game.end()) {
        if (game.current_player == LEFT) {
            game.walk();
        } else {
            int x;
            cout << "Player Move: ";
            cin >> x;
            game.move(x);
        }

        printBoard(game.gameBoard);
        cout << endl;
    }

    return 0;
}
