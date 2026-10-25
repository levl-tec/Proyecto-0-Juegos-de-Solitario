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
    inline static int cardsInTheBoard = 35;
    int score = 0;
    int round = 0;
    inline static int globalScore = 0;

public:

    GolfBoard(Column stockpile, Column discardpile, List<Column*>* board) {
        this->board = board;
        this->stockpile = stockpile;
        this->discardpile = discardpile;
    }

    GolfBoard() {}

    void sumatory() {
        if (cardsInTheBoard == 0)
            score -= stockpile.getSize();
        else   
            score += cardsInTheBoard;
    }

    void discardCard(int columnPos) {
        board->goToPos(columnPos);
        Column* column = board->getElement();
        if (isValidDiscard(column->getLastCard())) {
            discardpile.addCard(column->removeCard());
            cardsInTheBoard--;
        }
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
        globalScore += score;
        cardsInTheBoard = 35;
    }

    bool isThereAValidMove() {
        if (cardsInTheBoard == 0)
            return 0;
        board->goToStart();
        for (int i = 0; i < board->getSize(); i++) {
            if(isValidDiscard(board->getElement()->getLastCard()))
                return 1;
            board->next();
        }
        return 0;
    }
};