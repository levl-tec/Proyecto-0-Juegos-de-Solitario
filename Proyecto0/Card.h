#pragma once

#include <iostream>
#include <string>

class Carta {
private:
    char rank;
    bool faceUp;
    int value;

public:

    Carta(char palo, int value, bool vision) {
        this->rank = rank;
        this->faceUp = faceUp;
        this-> value = value;
    }

    Carta() {}

    int getValue() {
        return value;
    }

    friend std::ostream& operator<<(std::ostream& os, Carta c) {
        std::string simbolo;

        switch (c.rank) {
            case 'S':
                simbolo = "♠";
                break;
            case 'H':
                simbolo = "♥";
                break;
            case 'D':
                simbolo = "♦";
                break;
            case 'C':
                simbolo = "♣";
                break;
        }

        std::string rango;

        switch (c.value) {
            case 1:
                rango = "A";
                break;
            case 11:
                rango = "J";
                break;
            case 12:
                rango = "Q";
                break;
            case 13:
                rango = "K";
                break;
            default:
                rango = std::to_string(c.value);

        }

        os << "┌─────────┐\n";
        os << "│ " << rango << std::string(2 - rango.size(), ' ')
           << "      │\n";
        os << "│         │\n";
        os << "│    " << simbolo << "    │\n";
        os << "│         │\n";
        os << "│       " << rango
           << std::string(2 - rango.size(), ' ') << "│\n";
        os << "└─────────┘";
        return os;
    }

};