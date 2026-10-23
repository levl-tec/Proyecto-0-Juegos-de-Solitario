#pragma once

#include <iostream>
#include "Board.h"

class GameState {
private:
    Board board;

public:

    GameState() {}

    GameState(Board board) {
        this->board = board;
    }
};