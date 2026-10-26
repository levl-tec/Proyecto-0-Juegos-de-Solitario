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

    // Returns a NEW list with copies of the cards from index 'start' to the end
    // of the column. It only extracts: it does not check the order of the cards
    // and it does not modify the column. The caller must delete the returned list.
    List<Card>* getSlice(int start) {
        int size = cards->getSize();

        if (start < 0 || start >= size)
            throw std::runtime_error("Inicio de seccion (slice) invalido");

        return cards->slice(start, size - 1);
    }

    // True if every card is exactly one value lower than the previous one
    // (for example 9, 8, 7). A list with 0 or 1 cards counts as a run.
    // Positions here are in the list that is passed in, which starts at 0.
    static bool isRun(List<Card>* run) {
        run->goToStart();
        for (int i = 0; i < run->getSize() - 1; i++) {
            Card first = run->getElement();
            run->next();
            Card second = run->getElement();
            if (first.getValue() != second.getValue() + 1)
                return false;
        }
        return true;
    }

    Card removeCard() {
        if (cards->getSize() == 0)
            throw std::runtime_error("La columna esta vacia");

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

    void clear() {
        cards->clear();
    }

    void fillShuffled(const char* suits, int sets) {
        cards->clear();

        List<Card>* temp = new ArrayList<Card>(13 * sets);

        for (int i = 0; i < sets; i++) {

            for (int j = 1; j < 14; j++) {
                Card card = Card(suits[i], j, 0);
                temp->append(card);
            }
        }

        int size = temp->getSize();
        while (size != 0) {
            int num = rand() % temp->getSize();
            temp->goToPos(num);
            Card card = temp->remove();
            addCard(card);
            size = temp->getSize();
        }

        delete temp;
    }

    void isValidColumnMove(List<Card>* newCards) {
        if (newCards->getSize() == 0)
            throw std::runtime_error("No hay cartas para mover");

        if (cards->getSize() == 0)
            return;

        newCards->goToStart();
        if (this->getLastCard().getValue() != newCards->getElement().getValue() + 1)
            throw std::runtime_error("Debe colocar las Cartas sobre una carta de valor inmediatamente mayor");
    }

    void flipLastCard() {
        if (cards->getSize() == 0)
            return;
        cards->goToEnd();
        cards->previous();
        Card c = cards->getElement();
        c.setVisibility(true);
        cards->setElement(c);
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
