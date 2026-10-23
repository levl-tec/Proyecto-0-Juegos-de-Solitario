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
    List<Column>* board = new ArrayList<Column>(7);
    Column stockpile;
    Column discardpile;
    static int score;

public:
    int contarPuntos() {
        int sum = 0;
        for (int i = 0; i < board->getSize(); i++) {
            sum += board->getElement().getSize();
        }
        sum -= stockpile.getSize();
    }
};