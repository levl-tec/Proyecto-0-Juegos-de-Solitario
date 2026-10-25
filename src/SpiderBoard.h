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
    inline static int nextEmptyFoundation = 0;

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
        //Indica el indice apartir de donde se tienen que sacar las cartas
        int indexStart = column->getSize()-amountOfCards;
        //Obtiene las cartas sin eliminarlas de la columna
        List<Card>* cardsMoved = column->getSlice(indexStart);
        //Se mueve a la columna de destino
        board->goToPos(columnDestiny);
        //Extrae la columna
        Column* column2 = board->getElement();
        //Comprueba si el movimiento es valido, si la comprobacion es correcta sigue con el programa si no lanza una excepcion
        column2->isValidColumnMove(cardsMoved);
        //Si el movimien si es valido ahora si elimina las cartas de la columna de la que se sacaron
        column->removeSlice(indexStart);
        //Seguidamente a eso anade las cartas que se extrajeron inicialmente
        column2->addCards(cardsMoved);
        //Se mueve al final (recordar que es una DLinkedList, esta tiene 2 nodos 
        //sentinela vacios por lo que no nos movemos al final si no que al anterior al final)
        cardsMoved->goToEnd();
        cardsMoved->previous();
        //Revisa si la columna es de un tamano mayor o igual a 13 y si ultima carta es un As
        if (cardsMoved->getElement().getValue() == 1 && column2->getSize() >= 13) {
            //Si cumple con las anteriores condiciones revisa si es una secuencia completa
            if (isCompleteSecuence(column2->getSlice(column2->getSize()-13))) {
                //Si si es una secuencia completa la elimina de la columna destino y la agrega a las foundations
                foundations->goToPos(nextEmptyFoundation);
                foundations->getElement()->addCards(column2->removeSlice(column2->getSize()-13));
                nextEmptyFoundation++;
            }
        }
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