#ifndef GAME_H
#define GAME_H

#include "tile.h"
#include <vector>
#include <tuple>

class Game
{
public:
    Game(int, int, int);
    Tile** board;
    int rows;
    int cols;
    int mines;
    bool running;

    void printBoard();
    std::vector<std::tuple<int, int>> getNeighbours(int, int);
    void reveal(int, int);
    void revealNeighbours(int, int);
    void end();
private:

    Tile** generateBoard();
    bool checkLoc(Tile *);
};

#endif // GAME_H