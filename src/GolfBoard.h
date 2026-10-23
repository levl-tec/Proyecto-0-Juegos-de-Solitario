#pragma once

#include <iostream>
#include "ArrayList.h"
#include "Stack.h"
#include "LinkedStack.h"
#include "Board.h"
#include "Column.h"
#include "List.h"

class GolfBoard : public Board {
private:
    List<Column>* board;
    Column stockpile;
    Column discardpile;
    static int score;
    static int round;

public:

    GolfBoard(Column stockpile, Column discardpile, List<Column>* board) {
        this->board = new ArrayList<Column>(7);
        this->stockpile = stockpile;
        this->discardpile = discardpile;
        this->score = 0;
        this->round = 0;
        this->round++;
    }

    GolfBoard() {}

    int contarPuntos() {
        int sum = 0;
        for (int i = 0; i < board->getSize(); i++) {
            sum += board->getElement().getSize();
        }
        sum -= stockpile.getSize();
    }
};