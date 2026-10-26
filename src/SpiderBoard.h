#pragma once 

#include <iostream>
#include <stdexcept>
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
    int nextEmptyFoundation = 0;
    
    

    bool checkCompletedRun(Column* column) {
        if (column->getSize() == 0)
            return 0;

        //Revisa si la columna es de un tamano mayor o igual a 13 y si la ultima carta es un As
        if (column->getLastCard().getValue() == 1 && column->getSize() >= 13) {
            //Si cumple con las anteriores condiciones revisa si es una secuencia completa
            List<Card>* lastThirteen = column->getSlice(column->getSize() - 13);
            bool complete = isCompleteSecuence(lastThirteen);
            delete lastThirteen;
            if (complete) {
                //Si si es una secuencia completa la elimina de la columna destino y la agrega a las foundations
                List<Card>* sequence = column->removeSlice(column->getSize() - 13);
                foundations->goToPos(nextEmptyFoundation);
                foundations->getElement()->addCards(sequence);
                delete sequence;
                nextEmptyFoundation++;
                column->flipLastCard();
                return 1;
            }
        }
        return 0;
    }

public:

    SpiderBoard(Column stockpile, List<Column*>* board) {
        foundations = new ArrayList<Column*>(8);
        this->board = board;
        this->stockpile = stockpile;
        for (int i = 0; i < 8; i++) {
            foundations->append(new Column());
        }
    }

    SpiderBoard() {
        board = new ArrayList<Column*>(10);
        for (int i = 0; i < 10; i++) {
            board->append(new Column());
        }

        char suits[8] = { 'S', 'S', 'S', 'S', 'S', 'S', 'S', 'S' };
        stockpile.fillShuffled(suits, 8);
        
        board->goToStart();
        int count = 6;
        for (int i = 0; i < 10; i++) {

            if (i > 3) 
                count = 5;

            for (int j = 0; j < count; j++) {
                Card c = stockpile.removeCard();
                if (j == count - 1)
                    c.setVisibility(true);
                board->getElement()->addCard(c);
            }
            board->next();
        }

        foundations = new ArrayList<Column*>(8);
        for (int i = 0; i < 8; i++) {
            foundations->append(new Column());
        }
    }

    

    bool changeColumn(int columnOrigin, int columnDestiny, int amountOfCards) {
        if (columnDestiny == columnOrigin)
            throw std::runtime_error("Las columnas de origen y destino deben ser diferentes");
        //Va a la columna de la que se van a sacar las cartas
        board->goToPos(columnOrigin - 1);
        //Extrae la columna
        Column* column = board->getElement();
        //Se mueve a la columna de destino y la extrae (antes de crear la lista, por si el numero es invalido)
        board->goToPos(columnDestiny - 1);
        Column* column2 = board->getElement();
        
        if (amountOfCards > column->getSize()) {
            throw std::runtime_error("La columna no tiene suficientes cartas");
        }
        
        //Indica el indice apartir de donde se tienen que sacar las cartas
        int indexStart = column->getSize() - amountOfCards;
        //Obtiene las cartas sin eliminarlas de la columna (lanza excepcion si el indice es invalido)
        List<Card>* cardsMoved = column->getSlice(indexStart);
        //Comprueba que las cartas movidas sean una secuencia y que encajen en el destino.
        //Si algo falla se libera la lista y se lanza la excepcion antes de modificar ninguna columna
        try {
            cardsMoved->goToStart();
            Card c = cardsMoved->getElement();
            if (!c.isVisible())
                throw std::runtime_error("Solo puede mover cartas que esten visibles");
            if (!Column::isRun(cardsMoved))
                throw std::runtime_error("Las cartas deben estar en orden ascendente");
            column2->isValidColumnMove(cardsMoved);
        }
        catch (...) {
            delete cardsMoved;
            throw;
        }
        //Si el movimiento si es valido ahora si elimina las cartas de la columna de la que se sacaron
        List<Card>* removed = column->removeSlice(indexStart);
        delete removed;
        //Seguidamente a eso anade las cartas que se extrajeron inicialmente
        column2->addCards(cardsMoved);
        delete cardsMoved;
        column->flipLastCard();
        
        return checkCompletedRun(column2);
    }

    bool isCompleteSecuence(List<Card>* columnSlice) {
        columnSlice->goToStart();
        for (int i = 0; i < 13; i++) {
            Card fCard = columnSlice->getElement();
            
            if (!fCard.isVisible())
                return false;

            if (i < 12) {
                columnSlice->next();
                Card sCard = columnSlice->getElement();
                if (!(fCard.getValue() > sCard.getValue()))
                    return false;
            }
        }
        return true;
    }

    int dealRow() {
        if (stockpile.getSize() == 0)
            throw std::runtime_error("No quedan cartas para repartir");
        
        board->goToStart();
        for (int i = 0; i < 10; i++) {
            if (board->getElement()->getSize() == 0)
                throw std::runtime_error("Todas las columnas deben tener al menos una carta");
            board->next();
        }


        board->goToStart();
        for (int i = 0; i < 10; i++) {

            Card c = stockpile.removeCard();
            c.setVisibility(true);
            board->getElement()->addCard(c);

            board->next();
        }

        board->goToStart();
        int completedRuns = 0;
        for (int i = 0; i < 10; i++) {
            if (checkCompletedRun(board->getElement()))
                completedRuns++;
            board->next();
        }

        return completedRuns;
    }

    bool isGameWon() {
        return (nextEmptyFoundation == 8);
    }

    int getCompletedRuns() {
        return nextEmptyFoundation;
    }
 
    int getDealsLeft() {
        return (stockpile.getSize() / 10);
    }

    Board* clone() {
        SpiderBoard* copy = new SpiderBoard(*this);
        copy->stockpile = stockpile.copy();
        
        copy->board = new ArrayList<Column*>(10);
        board->goToStart();
        for (int i = 0; i < board->getSize(); i++) {
            Column* c = board->getElement();

            copy->board->append(new Column(c->copy()));
            board->next();
        }

        copy->foundations = new ArrayList<Column*>(8);
        foundations->goToStart();
        for (int i = 0; i < foundations->getSize(); i++) {
            Column* c = foundations->getElement();

            copy->foundations->append(new Column(c->copy()));
            foundations->next();
        }

        return copy;
    }

};
