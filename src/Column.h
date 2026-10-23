#pragma once

#include <iostream>
#include "Card.h"
#include "DLinkedList.h"

class Column {
private:
List<Card>* cards;


public:
    Column(List<Card>* cards) {
        this->cards = cards;
    }

    Column() {}

    int getSize() {
        return cards->getSize();
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
