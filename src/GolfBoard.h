#pragma once

#include <iostream>
#include <cmath>
#include "ArrayList.h"
#include "Stack.h"
#include "LinkedStack.h"
#include "Board.h"
#include "Column.h"
#include "List.h"

class GolfBoard : public Board {
private:
    List<Column*>* board;
    Column stockpile;
    Column discardpile;
    int score = 0;
    int round = 0;

public:

    GolfBoard(Column stockpile, Column discardpile, List<Column*>* board) {
        this->board = board;
        this->stockpile = stockpile;
        this->discardpile = discardpile;
    }

    GolfBoard() {}

    void sumatory() {
        int sum = 0;
        for (int i = 0; i < board->getSize(); i++) {
            sum += board->getElement()->getSize();
        }
        sum -= stockpile.getSize();
        score = score + sum;
    }

    void discardCard(int columnPos) {
        board->goToPos(columnPos);
        Column* column = board->getElement();
        if (isValidDiscard(column->getLastCard()))
            discardpile.addCard(column->removeCard());
    }

    bool isValidDiscard(Card cardToDiscard) {
        int valueCardToDiscard = cardToDiscard.getValue();
        int valueDiscardPileCard = discardpile.getLastCard().getValue(); 
        if (valueCardToDiscard == 1 && valueDiscardPileCard == 13 || valueCardToDiscard == 13 && valueDiscardPileCard == 1)
            return 1;
        int difference = valueCardToDiscard - valueDiscardPileCard;
        return abs(difference) == 1;
    }

    void nextRound() {
        round++;
        sumatory();
    }

};