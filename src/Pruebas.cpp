#include <iostream>
#include <windows.h>
#include <cstdlib>
#include "Board.h"
#include "Card.h"
#include "DLinkedList.h"
#include "ArrayStack.h"
#include "GameState.h"
#include "GolfBoard.h"
#include "SpiderBoard.h"
#include "Column.h"



int pruebas()
{
    std::cout << "Entre a pruebas()" << std::endl;
    char* ranks = new char [4] {'S', 'C', 'H', 'D'};
    Column stockpile = Column();
    srand(time(0));
    for (int i = 0; i < 4; i++) {
        List<Card>* cardSecuence = new ArrayList<Card>(13);
        for (int j = 1; j < 14; j++) {
            Card card = Card(ranks[i], j, 1);
            cardSecuence->append(card);
        }

        std::cout << "Mezclando Palo" << std::endl;
        int size = cardSecuence->getSize();
        while (size != 0) {
            std::cout << size << std::endl;
            int num = rand() % cardSecuence->getSize();
            std::cout << "Creando Numero aleatorio" << std::endl;
            cardSecuence->goToPos(num);
            std::cout << "Yendo al numero" << std::endl;
            Card card = cardSecuence->remove();
            std::cout << "Saque la carta" << std::endl;
            stockpile.addCard(card);
            std::cout << "Agregue la carta" << std::endl;
            size = cardSecuence->getSize();
            std::cout << size << std::endl;
        }
    }

    std::cout << "Se creo el stockpile" << std::endl;
    
    List<Column*>* board = new ArrayList<Column*>(7);
    for (int j = 0; j < 7; j++) {
        std::cout << "Creando columna" << std::endl;
        List<Card>* columnCards = new DLinkedList<Card>();
        for (int k = 0; k < 5; k++) {
            columnCards->append(stockpile.removeCard());
        }
        Column* column = new Column(columnCards);
        board->append(column);
    }
    
     std::cout << "Se creo el board" << std::endl;

    Column discardpile;
    discardpile.addCard(stockpile.removeCard());

    std::cout << "Antes de crear el GolfBoard" << std::endl;

    Board* golf = new GolfBoard(stockpile, discardpile, board);

    std::cout << "Se creo el golfboard correctamente" << std::endl;

    std::cout << "Sali de pruebas()" << std::endl;
    return 0;
}
