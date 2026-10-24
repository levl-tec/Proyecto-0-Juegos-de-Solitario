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



int main()
{
    char* ranks = new char [4] {'S', 'C', 'H', 'D'};
    Column stockpile = Column();
    srand(time(0));
    for (int i = 0; i < 4; i++) {
        List<Card>* cardSecuence = new ArrayList<Card>(13);
        for (int j = 1; j < 14; j++) {
            Card card = Card(ranks[i], j, 1);
            cardSecuence->append(card);
        }
        while (cardSecuence->getSize() != 0) {
            int num = rand() % cardSecuence->getSize();
            cardSecuence->goToPos(num);
            stockpile.addCard(cardSecuence->remove());
        }
    }
    // for (int i = 0; i < 35; i++) {
    //     stockpile.removeCard();
        
    // }

    // Column discardpile = Column();
    // discardpile.addCard(stockpile.removeCard());
    // GolfBoard golf = GolfBoard(stockpile, discardpile, List<Column*>* board);


    return 0;
}
