#pragma once

#include <iostream>
#include "Carta.h"
#include "DLinkedList.h"

class PilaCartas {
private:
 List<Carta>* cartas;

public:
    PilaCartas(List<Carta>* cartas) {
        this->cartas = cartas;
    }

    PilaCartas() {}

    friend std::ostream& operator<<(std::ostream& os, PilaCartas pila) {
        for (int i = 0; i < pila.cartas->getSize(); i++) {
            std::cout << pila.cartas->getElement() << '\n';
            pila.cartas->next();
        }
        return os;
    }
};