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
};