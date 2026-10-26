#pragma once

#include <iostream>
#include "Board.h"

class GameState {
private:
    Board* board;

public:

    GameState() {}

    GameState(Board* board) {
        this->board = board;
    }

    Board* getBoard() {
        return board;
    }

    friend std::ostream& operator<<(std::ostream& os, GameState c) {
        os << "[Estado]";
        return os;
    }
};