#pragma once

#include <iostream>
#include "ArrayList.h"
#include "DLinkedList.h"
#include "LinkedStack.h"
#include "PilaCartas.h"
#include "Carta.h"

class Estado {
private:
    List<PilaCartas>* cartasEnMesa;
    Stack<Carta>* mazo;

public:

    Estado() {}

    
    void print() {
        //Hay que hacer que este metodo imprima las columnas de pilas de una forma horizontal
        //Esto haciendolo simplemente imprimiendo cada columna no funciona, ya lo probe y no funciono :( por lo que 
        //hay que buscar la forma de hacer esto para realizar la impresion correctamente, la otra opcion es en vez de imprimir toda la columna 
        // disenar la manera de que imprima solo el pedacito de arriba de las cartas e imprima completa la que esta en frente, para asi ahorrar
        // espacio, este arreglo se haria en el os<< de PilaCartas.h, sin embargo incluso con ese arreglo hay que encontrar la manera de 
        // imprimir las columnas horizontalmente
    }
};