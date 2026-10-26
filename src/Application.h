#pragma once

#include "GameState.h"
#include "Stack.h"
#include "LinkedStack.h"

class Application {

private:
    Stack<GameState>* future;
    Stack<GameState>* past;
    GameState actual;

    void emptyStack(Stack<GameState>* s) {
        while (!s->isEmpty()) {
            GameState st = s->pop();
            delete st.getBoard();
        }
    }

public:

    Application(GameState actual) {
        this->future = new LinkedStack<GameState>();
        this->past = new LinkedStack<GameState>();
        this->actual = actual;
    }

    void changeState(GameState newState) {
        emptyStack(future);
        
        past->push(actual);
        this->actual = newState;
    }

    void goToPast() {
        if (past->getSize() == 0)
            throw std::runtime_error("No hay jugadas para deshacer");
        future->push(actual);
        this->actual = past->pop();
    }

    void goToFuture() {
        if (future->getSize() == 0)
            throw std::runtime_error("No hay jugadas para rehacer");
        past->push(actual);
        this->actual = future->pop();
    }

    Board* getCurrent() {
        return actual.getBoard();
    }

    void clearHistory() {
        emptyStack(future);
        emptyStack(past);
    }

};