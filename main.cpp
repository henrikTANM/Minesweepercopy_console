#include "game.h"
#include <stdio.h>
#include <iostream>
#include <string>


using namespace std;

int main(int argc, char *argv[])
{
    Game *game = new Game(16, 16, 40);

    while(game->running) {
        game->printBoard();
        cout << "\n" <<"Reveal tile as(<row,column> - enter correctly, currently no error handiling!): ";
        string input;
        cin >> input;
        cout << "\n";

        int row = stoi(input.substr(0, input.find(",")));
        int column = stoi(input.substr(input.find(",") + 1, input.length() - input.find(",") + 1));

        game->reveal(row, column);
    }

    return 0;
}