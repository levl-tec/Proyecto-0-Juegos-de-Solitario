#pragma once

#include <iostream>
#include "ArrayList.h"
#include "Stack.h"
#include "LinkedStack.h"
#include "Board.h"
#include "PilaCartas.h"
#include "List.h"

class GolfBoard : public Board {
private:
    List<PilaCartas>* board = new ArrayList<PilaCartas>(7);
    PilaCartas stockpile;
    PilaCartas discardpile;
    static int score;

public:
    int contarPuntos() {
        int sumatoria = 0;
        for (int i = 0; i < board->getSize(); i++) {
            sumatoria += board->getElement().getSize();
        }
        sumatoria -= stockpile.getSize();
    }
};