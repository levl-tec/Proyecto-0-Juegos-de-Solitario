#pragma once

#include <iostream>
#include "Card.h"
#include "DLinkedList.h"
#include "typeOfColumn.h"

class Column {
private:
    List<Card>* cards;
    typeOfColumn type;

public:
    Column(List<Card>* cards, typeOfColumn type) {
        this->cards = cards;
        this->type = type;
    }

    Column() {}

    int getSize() {
        return cards->getSize();
    }

    List<Card>* moveCards(int start, int end) {
        List<Card>* columnSlice = cards->slice(start, end);
        cards->goToPos(start);
        for (int i = 0; i < columnSlice->getSize(); i++) {
            cards->remove();
            cards->next();
        }
        return columnSlice;
    }

    Card removeCard() {
        cards->goToEnd();
        return cards->remove();
    }

    void addCards(List<Card>* newCards) {
        newCards->goToStart();
        for (int i = 0; i < newCards->getSize(); i++) {
            cards->append(newCards->getElement());
            newCards->next();
        }
    }

    void addCard(Card newCard) {
        cards->append(newCard);
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
