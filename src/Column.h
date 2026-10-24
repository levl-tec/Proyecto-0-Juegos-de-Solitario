#pragma once

#include <iostream>
#include <stdexcept>
#include "Card.h"
#include "DLinkedList.h"

class Column {
private:
    List<Card>* cards;

public:
    Column(List<Card>* cards) {
        this->cards = cards;
    }

    Column() {
        cards = new DLinkedList<Card>();
    }

    int getSize() {
        return cards->getSize();
    }

    List<Card>* getCards() {
        return cards;
    }

    Card getLastCard() {
        cards->goToEnd();
        cards->previous();
        return cards->getElement();
    }

    List<Card>* removeCards(int start) {
        int size = cards->getSize();
        List<Card>* columnSlice = cards->slice(start, size-1);
        cards->goToPos(start);
        for (int i = 0; i < size; i++) {
            Card fCard = cards->remove();
            if (!(cards->atEnd())) {
                cards->next();
                Card sCard = cards->remove();
                if (!(fCard.getValue() > sCard.getValue()))
                    throw std::runtime_error("CARDS MUST BE IN ASCENDING ORDER");
            }
        }
        return columnSlice;
    }

    Card removeCard() {
        if (cards->getSize() == 0)
            throw std::runtime_error("Column is empty");

        cards->goToPos(cards->getSize() - 1);
        return cards->remove();
    }

    void addCards(List<Card>* newCards) {
        newCards->goToStart();
        for (int i = 0; i < newCards->getSize(); i++) {
            newCards->next();
            cards->append(newCards->getElement());
        }
    }

    void addCard(Card newCard) {
        cards->append(newCard);
    }

    void isValidColumnMove(List<Card>* newCards) {
        newCards->goToPos(1);
        cards->goToPos(cards->getSize()-1);
        if (cards->getElement().getValue() <= newCards->getElement().getValue())
            throw std::runtime_error("CARDS MUST STAY IN ASCENDING ORDER");
    }

//     friend std::ostream& operator<<(std::ostream& os, Column pila) {
//         for (int i = 0; i < pila.cards->getSize(); i++) {
//             std::cout << pila.cards->getElement() << '\n';
//             pila.cards->next();
//         }
//         return os;
// <<<<<<<< HEAD:src/Column.h
//     } //ESTO VA AL RENDERER
// };
// ========
//     }
};

// >>>>>>>> origin/main:src/PilaCartas.h
