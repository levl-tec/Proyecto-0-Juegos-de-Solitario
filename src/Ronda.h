#pragma once

#include <iostream>
#include <stdexcept>
#include "LinkedStack.h"
#include "Estado.h"

class Ronda {
private:
    Stack<Estado>* futuro;
    Stack<Estado>* pasado;
    Estado actual;
    int numRonda;

public:

    Ronda(Estado actual, int numRonda) {
        this->futuro = new LinkedStack<Estado>();
        this->pasado = new LinkedStack<Estado>();
        this->actual = actual;
        this->numRonda = numRonda;
    }

    void cambiarEstado(Estado nuevoEstado) {
        if (futuro->getSize() != 0)
            futuro->clear();
        pasado->push(actual);
        this->actual = nuevoEstado;
    }

    void irAlPasado() {
        if (pasado->getSize() == 0)
            throw std::runtime_error("NO HAY PASADO");
        futuro->push(actual);
        this->actual = pasado->pop();
    }

    void irAlFuturo() {
        if (futuro->getSize() == 0)
            throw std::runtime_error("NO HAY FUTURO");
        pasado->push(actual);
        this->actual = futuro->pop();
    }

    int getNumRonda() {
        return numRonda;
    }
};