#pragma once

#include <iostream>
#include <string>


class Card {
private:
    char rank;
    bool faceUp;
    int value;

public:

    Card(char rank, int value, bool faceUp) {
        this->rank = rank;
        this->faceUp = faceUp;
        this->value = value;
    }

    Card() {}

    int getValue() {
        return value;
    }

    bool isVisible() {
        return faceUp;
    }

    void setVisibility(bool faceUp) {
        this->faceUp = faceUp;
    }

    char getSuit() {
        return rank;
    }

    friend std::ostream& operator<<(std::ostream& os, Card c) {
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