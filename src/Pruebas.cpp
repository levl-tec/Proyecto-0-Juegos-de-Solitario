#include <iostream>
#include <windows.h>
#include "PilaCartas.h"
#include "Carta.h"
#include "DLinkedList.h"
#include "ArrayStack.h"
#include "Estado.h"

int pruebas()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Carta cartaPrueba = Carta('S', 1, 1);
    Carta cartaPrueba2 = Carta('H', 13, 1);
    Carta cartaPrueba3 = Carta('D', 2, 1);
    Carta cartaPrueba4 = Carta('C', 12, 1);
    std::cout << cartaPrueba;
    std::cout << '\n' << '\n';
    std::cout << (cartaPrueba.getValue() > cartaPrueba2.getValue()) << '\n';

    std::cout << "Inicio pruebas pilasCartas, mazo, estado" << '\n';
    List<Carta>* cartas = new DLinkedList<Carta>();
    List<Carta>* cartas2 = new DLinkedList<Carta>();
    cartas->append(cartaPrueba);
    cartas->append(cartaPrueba2);
    cartas2->append(cartaPrueba3);
    cartas2->append(cartaPrueba4);
    PilaCartas pilaCartas = PilaCartas(cartas);
    PilaCartas pilaCartas2 = PilaCartas(cartas2);
    List<PilaCartas>* pilasCartas = new ArrayList<PilaCartas>(7);
    pilasCartas->append(pilaCartas);
    pilasCartas->append(pilaCartas2);
    Stack<Carta>* mazo = new ArrayStack<Carta>();
    return 0;
}
