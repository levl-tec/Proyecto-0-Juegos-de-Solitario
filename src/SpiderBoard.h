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
        if (columnDestiny == columnOrigin)
            throw std::runtime_error("The origin and destiny column must be different");
        //Va a la columna de la que se van a sacar las cartas
        board->goToPos(columnOrigin);
        //Extrae la columna
        Column* column = board->getElement();
        //Se mueve a la columna de destino y la extrae (antes de crear la lista, por si el numero es invalido)
        board->goToPos(columnDestiny);
        Column* column2 = board->getElement();
        //Indica el indice apartir de donde se tienen que sacar las cartas
        int indexStart = column->getSize() - amountOfCards;
        //Obtiene las cartas sin eliminarlas de la columna (lanza excepcion si el indice es invalido)
        List<Card>* cardsMoved = column->getSlice(indexStart);
        //Comprueba que las cartas movidas sean una secuencia y que encajen en el destino.
        //Si algo falla se libera la lista y se lanza la excepcion antes de modificar ninguna columna
        try {
            if (!Column::isRun(cardsMoved))
                throw std::runtime_error("CARDS MUST BE IN ASCENDING ORDER");
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
        //Revisa si la columna es de un tamano mayor o igual a 13 y si la ultima carta es un As
        if (column2->getLastCard().getValue() == 1 && column2->getSize() >= 13) {
            //Si cumple con las anteriores condiciones revisa si es una secuencia completa
            List<Card>* lastThirteen = column2->getSlice(column2->getSize() - 13);
            bool complete = isCompleteSecuence(lastThirteen);
            delete lastThirteen;
            if (complete) {
                //Si si es una secuencia completa la elimina de la columna destino y la agrega a las foundations
                List<Card>* sequence = column2->removeSlice(column2->getSize() - 13);
                foundations->goToPos(nextEmptyFoundation);
                foundations->getElement()->addCards(sequence);
                delete sequence;
                nextEmptyFoundation++;
            }
        }
    }

    bool isCompleteSecuence(List<Card>* columnSlice) {
        columnSlice->goToStart();
        for (int i = 0; i < 13; i++) {
            Card fCard = columnSlice->getElement();
            if (i < 12) {
                columnSlice->next();
                Card sCard = columnSlice->getElement();
                if (!(fCard.getValue() > sCard.getValue()))
                    return false;
            }
        }
        return true;
    }

};
