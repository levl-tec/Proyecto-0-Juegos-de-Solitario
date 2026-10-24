
#pragma once

#include <iostream>
#include "Card.h"
#include "ArrayStack.h"

inline int probarCartas() {
    int errores = 0;

    std::cout << "\n--- Pruebas de Card ---\n";

    Card as('S', 1, true);
    Card rey('H', 13, false);

    if (as.getValue() == 1 && as.isVisible()) {
        std::cout << "Bien, As creado correctamente\n";
    }
    else {
        std::cout << "ERROR: Datos incorrectos en el as\n";
        errores++;
    }

    if (rey.getValue() == 13 && !rey.isVisible()) {
        std::cout << "Bien, Rey creado correctamente\n";
    }
    else {
        std::cout << "ERROR: Datos incorrectos en el rey\n";
        errores++;
    }

    return errores;
}

inline int probarMazo() {
    int errores = 0;

    std::cout << "\n--- Pruebas de mazo ---\n";

    ArrayStack<Card> mazo(52);
    char palos[4] = { 'S', 'C', 'H', 'D' };

    for (int i = 0; i < 4; i++) {
        for (int valor = 1; valor <= 13; valor++) {
            mazo.push(Card(palos[i], valor, false));
        }
    }

    if (mazo.getSize() == 52) {
        std::cout << "Bien, mazo con 52 cartas\n";
    }
    else {
        std::cout << "ERROR: Cantidad incorrecta\n";
        errores++;
    }

    int retiradas = 0;
    bool valoresValidos = true;

    while (!mazo.isEmpty()) {
        Card carta = mazo.pop();

        if (carta.getValue() < 1 || carta.getValue() > 13) {
            valoresValidos = false;
        }

        retiradas++;
    }

    if (retiradas == 52 && mazo.isEmpty() && valoresValidos) {
        std::cout << "Bien, se retiraron las 52 cartas\n";
    }
    else {
        std::cout << "ERROR: Problema al retirar cartas\n";
        errores++;
    }

    return errores;
}

inline void ejecutarPruebas() {
    int errores = 0;

    errores += probarCartas();
    errores += probarMazo();

    std::cout << "\nTotal de errores: " << errores << "\n";
}
