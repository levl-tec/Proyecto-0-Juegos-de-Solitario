#pragma once 

#include <iostream>
#include "ArrayList.h"
#include "Stack.h"
#include "LinkedStack.h"
#include "Board.h"
#include "Column.h"
#include "List.h"

class SpiderBoard : public Board {
private:
    List<Column*>* board;
    Column stockpile;
    List<Column*>* foundations;

public:

    SpiderBoard(Column stockpile, List<Column*>* board) {
        foundations = new ArrayList<Column*>(8);
        this->board = board;
        this->stockpile = stockpile;
        for (int i = 0; i < 8; i++) {
            foundations->append(new Column());
        }
    }

    SpiderBoard() {}

    void changeColumn(int columnOrigin, int columnDestiny, int amountOfCards) {
        board->goToPos(columnOrigin);
        Column* column = board->getElement();
        int indexStart = column->getSize()-amountOfCards;
        List<Card>* cardsMoved = column->removeCards(indexStart);
        board->goToPos(columnDestiny);
        Column* column = board->getElement();
        column->isValidColumnMove(cardsMoved);
        column->addCards(cardsMoved);
        cardsMoved->goToEnd();
        if (cardsMoved->getElement().getValue() == 1 && column->getSize() >= 13)
            if (isCompleteSecuence(column->removeCards(column->getSize()-12)))
                column->removeCards(column->getSize()-12);
    }

    boolean isCompleteSecuence(List<Card>* columnSlice) {
        columnSlice->goToStart();
        for (int i = 0; i < 13; i++) {
            Card fCard = columnSlice->getElement();
            if (i < 12) {
                columnSlice->next();
                Card sCard = columnSlice->getElement();
                if (!(fCard.getValue() > sCard.getValue()))
                    return 0;
            }
        }
        return 1;
    }
    
};