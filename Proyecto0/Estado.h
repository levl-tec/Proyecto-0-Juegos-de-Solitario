#pragma once

#include <iostream>
#include "ArrayList.h"
#include "DLinkedList.h"
#include "LinkedStack.h"
#include "PilaCartas.h"
#include "Carta.h"

class Estado {
private:
    List<PilaCartas()>* cartasEnMesa;
    Stack<Carta>* mazo;

public:
    Estado(Stack<Carta>* mazo, List<PilaCartas()>* cartasEnMesa) {
        this->cartasEnMesa = cartasEnMesa;
        this->mazo = mazo;
    }

    void print() {
        for (int i = 0; i < cartasEnMesa->getSize(); i++) {
            List<Carta>* pilaCartas = cartasEnMesa->getElement();
            cartasEnMesa->next();
            std::cout << pilaCartas;
        }
    }
};