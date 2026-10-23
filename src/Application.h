#pragma once

#include "GameState.h"
#include "Stack.h"
#include "LinkedStack.h"

class Application {

private:
    Stack<GameState>* future;
    Stack<GameState>* past;
    GameState actual;

public:

    Application(GameState actual) {
        this->future = new LinkedStack<GameState>();
        this->past = new LinkedStack<GameState>();
        this->actual = actual;
    }

    void changeState(GameState newState) {
        if (future->getSize() != 0)
            future->clear();
        past->push(actual);
        this->actual = newState;
    }

    void goToPast() {
        if (past->getSize() == 0)
            throw std::runtime_error("THERE'S NO PAST");
        future->push(actual);
        this->actual = past->pop();
    }

    void goToFuture() {
        if (future->getSize() == 0)
            throw std::runtime_error("THERE'S NO FUTURE");
        past->push(actual);
        this->actual = future->pop();
    }
};