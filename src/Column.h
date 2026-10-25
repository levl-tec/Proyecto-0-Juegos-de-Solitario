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

    List<Card>* removeSlice(int start) {
        List<Card>* columnSlice = getSlice(start);

        int amount = cards->getSize() - start;

        cards->goToPos(start);

        for (int i = 0; i < amount; i++) {
            cards->remove();
        }
        return columnSlice;
    }

    List<Card>* getSlice(int start) {
        int size = cards->getSize();

        if (start < 0 || start >= size)
            throw std::runtime_error("Invalid slice start");

        List<Card>* columnSlice = cards->slice(start, size-1);

        columnSlice->goToPos(start);

        for (int i = 1; i < columnSlice->getSize(); i++) {
            Card fCard = columnSlice->getElement();
            cards->next();
            Card sCard = columnSlice->getElement();
            if (fCard.getValue() != sCard.getValue() + 1)
                throw std::runtime_error("CARDS MUST BE IN ASCENDING ORDER");
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
            cards->append(newCards->getElement());
            newCards->next();
        }
    }

    void addCard(Card newCard) {
        cards->append(newCard);
    }

    void isValidColumnMove(List<Card>* newCards) {
        if (newCards->getSize() == 0)
            throw std::runtime_error("No cards to move");

        if (cards->getSize() == 0)
            return;

        newCards->goToStart();
        if (this->getLastCard().getValue() != newCards->getElement().getValue() + 1)
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
