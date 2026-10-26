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
    Column stockPile;
    Column discardPile;
    int cardsInTheBoard = 35;
    int score = 0;
    int round = 1;
    int globalScore = 0;

public:

    GolfBoard(Column stockpile, Column discardpile, List<Column*>* board) {
        this->board = board;
        this->stockPile = stockpile;
        this->discardPile = discardpile;
    }

    GolfBoard() {}

    void sumatory() {
        if (cardsInTheBoard == 0)
            score -= stockPile.getSize();
        else   
            score += cardsInTheBoard;
    }

    void discardCard(int columnPos) {
        board->goToPos(columnPos-1);
        Column* column = board->getElement();

        if (column->getSize() == 0)
            throw std::runtime_error("La columna esta vacia!");
        
        if (!isValidDiscard(column->getLastCard()))
            throw std::runtime_error("La carta debe ser contigua a la del descarte");

        discardPile.addCard(column->removeCard());
        cardsInTheBoard--;
        
    }

    bool isValidDiscard(Card cardToDiscard) {
        int valueCardToDiscard = cardToDiscard.getValue();
        int valueDiscardPileCard = discardPile.getLastCard().getValue(); 
        if (((valueCardToDiscard == 1) && (valueDiscardPileCard == 13)) || 
            ((valueCardToDiscard == 13) && (valueDiscardPileCard == 1)))
            return 1;
        int difference = valueCardToDiscard - valueDiscardPileCard;
        return abs(difference) == 1;
    }

    void flipStockCard() {
        if (stockPile.getSize() == 0)
            throw std::runtime_error("El mazo esta vacio!");

        Card c = stockPile.removeCard();
        c.setVisibility(true);
        discardPile.addCard(c);
    }

    void nextRound() {
        round++;
        sumatory();
        globalScore += score;
        score = 0;
        cardsInTheBoard = 35;
    }

    bool isThereAValidMove() {
        if (cardsInTheBoard == 0)
            return 0;
        board->goToStart();
        for (int i = 0; i < board->getSize(); i++) {
            Column* c = board->getElement();
            if((c->getSize() > 0) && (isValidDiscard(c->getLastCard())))
                return 1;
            board->next();
        }
        return 0;
    }

    bool isRoundWon() {
        return (cardsInTheBoard == 0);
    }

    bool isRoundLost() {
        if (isRoundWon())
            return 0;
        return (stockPile.getSize() == 0) && (!isThereAValidMove());
    }

};