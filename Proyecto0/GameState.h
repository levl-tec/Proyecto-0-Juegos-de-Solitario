#pragma once

#include <iostream>
#include "ArrayList.h"
#include "DLinkedList.h"
#include "LinkedStack.h"
#include "Board.h"
#include "Carta.h"

class Estado {
private:
    Board* board;

public:

    Estado() {}
    Estado(Board* board) {

    }
};