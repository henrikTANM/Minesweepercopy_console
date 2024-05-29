#include "game.h"
#include "tile.h"
#include <vector>
#include <tuple>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

Game::Game(int rows, int cols, int mines) {
    this->running = true;
    this->rows = rows;
    this->cols = cols;
    this->mines = mines;
    this->board = generateBoard();
}

Tile** Game::generateBoard() {
    Tile** board = new Tile*[rows];
    for (int i = 0; i < rows; i++) {
        board[i] = new Tile[cols];
    }

    srand(time(NULL)|clock());

    for (int b = 0; b < mines; b++) {
        while(true) {
            int randX = rand() % (cols);
            int randY = rand() % (rows);
            Tile *randLoc = &board[randX][randY];
            if (randLoc->value != 'x') {
                randLoc->value = 'x';
                break;
            }
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Tile *current = &board[i][j];
            if (current->value != 'x') {
                vector<tuple<int, int>> neighbours = getNeighbours(i, j);
                int value = 0;
                for (tuple<int, int> tu : neighbours) {
                    if (board[get<0>(tu)][get<1>(tu)].value == 'x') { value++; }
                }
                current->value = '0' + value;
            }
        }
    }
    return board;
}

bool Game::checkLoc(Tile *tile) {
    return tile->value == 'x';
}

vector<tuple<int, int>> Game::getNeighbours(int i, int j) {
    vector<tuple<int, int>> *neighbours = new vector<tuple<int, int>>;

    if (i + 1 < rows) {
        neighbours->push_back(tuple(i+1, j));
        if (j + 1 < cols) { neighbours->push_back(tuple(i+1, j+1)); }
        if (j - 1 >= 0) { neighbours->push_back(tuple(i+1, j-1)); }
    }
    if (i - 1 >= 0) {
        neighbours->push_back(tuple(i-1, j));
        if (j + 1 < cols) { neighbours->push_back(tuple(i-1, j+1)); }
        if (j - 1 >= 0) { neighbours->push_back(tuple(i-1, j-1)); }
    }
    if (j + 1 < cols) { neighbours->push_back(tuple(i, j+1)); }
    if (j - 1 >= 0) { neighbours->push_back(tuple(i, j-1)); }

    return *neighbours;
}

void Game::reveal(int i, int j) {
    if (board[i][j].revealed == false) {
        board[i][j].revealed = true;
        if (board[i][j].value == '0') {
            revealNeighbours(i, j);
        }
        if (board[i][j].value == 'x') {
            //TODO reveal all
            this->running = false;
        }
    }
}

void Game::revealNeighbours(int i, int j) {
    vector<tuple<int, int>> neighbours = getNeighbours(i, j);
    for (tuple<int, int> tu : neighbours) {
        reveal(get<0>(tu), get<1>(tu));
    }
}

void Game::printBoard() {
    for (int i = 0; i < rows; ++i) {
        cout << "\n";
        for (int j = 0; j < cols; ++j) {
            if (board[i][j].revealed) { cout << board[i][j].value << " "; }
            else { cout << "- "; }
        }
        cout << " ";
        for (int j = 0; j < cols; ++j) {
            cout << board[i][j].value << " ";
        }
    }
}

void Game::end() {
    this->running = false;
}