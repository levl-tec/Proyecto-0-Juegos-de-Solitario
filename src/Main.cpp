#include <iostream>
#include <windows.h>
#include <string>
#include "List.h"
#include "PilaCartas.h"
#include "Carta.h"
#include "DLinkedList.h"
#include "ArrayStack.h"
#include "Estado.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

int main () {
    bienvenida();

    bool running = 1;
    while (running) {
        string eleccion = modoDeJuego(); //La idea es que el return sea 0 si es golf y 1 si es spider
        if (eleccion == "0")
            golf();
        if (eleccion == "1")
            spider();
        running = !running;
    }


    return 0;
}

void golf() {

}

void spider() {
    
}