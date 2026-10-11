#include <iostream>
#include <windows.h>
#include "Carta.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Carta cartaPrueba = Carta('S', 1, 1);
    Carta cartaPrueba2 = Carta('H', 13, 1);
    std::cout << cartaPrueba;
    std::cout << '\n' << '\n';
    std::cout << (cartaPrueba.getValue() > cartaPrueba2.getValue());
    return 0;
}
