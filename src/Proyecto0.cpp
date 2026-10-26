#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdio>
#include <ctime>
#include <string>
#include "Application.h"
#include "ArrayStack.h"
#include "Card.h"
#include "Column.h"
#include "DLinkedList.h"
#include "GameState.h"
#include "InteractionEngine.h"
#include "Renderer.h"

const bool RUN_TESTS = false; 
const bool RUN_MAIN = true;
const bool ADVANCED_UI = false;

int pruebas();



// ======================================================================
//
// Golf solitaire execution
//
// ======================================================================

void playGolf() {
    
    // Variables set up 
    InteractionEngine* ie = InteractionEngine::getInstance();
    Renderer* re = Renderer::getInstance();
    Application app(GameState(new GolfBoard()));
    std::string message = "";

    while (true) { // Start of Golf game loop
        GolfBoard* g = (GolfBoard*)app.getCurrent(); // Get game state
        
        if (g->isGameOver()) break; // Check for game end
        
        if (g->isRoundWon() || g->isRoundLost()) { // display round result message
            re->showGolf(g);
            if (g->isRoundWon())
                ie->showMessage("¡Ganó la ronda!");
            else
                ie->showMessage("Perdió la ronda: no quedan jugadas.");
            
            Board* next = g->clone(); // deep copy of game state
            int pts = ((GolfBoard*)next)->nextRound(); // advance round and store points
            app.changeState(GameState(next)); // update game state
            app.clearHistory(); // clear undo/redo history, since we're changing rounds
            ie->showMessage("Puntos de esta ronda: " + std::to_string(pts)); //  display rount points result

            if (!((GolfBoard*)next)->isGameOver()) // Do not display round counter after game is over (after round 9)
                ie->nextRound(((GolfBoard*)next)->getRound());
            continue;
        }
        
        re->clearScreen(); // Clear console
        re->showGolf(g); // Display on console 
        if (message.size() > 0) { // If there are messages, display them
            ie->showMessage(message);
            message = "";
        }


        if ((!g->isThereAValidMove()) && (g->getStockSize() > 0))
            ie->showMessage("No hay jugadas disponibles: voltee una carta del mazo.");
        
        int action = ie->selectAction(InteractionEngine::GOLF); // Get user input


        // User actions decision tree 
        if (action == InteractionEngine::ACCION_1) { // Action: Discard Card
            int col = ie->selectColumn(7);
            Board* next = g->clone();
            try {
                ((GolfBoard*)next)->discardCard(col);
                app.changeState(GameState(next));
            }
            catch (const std::runtime_error& e) {
                delete next;
                message = std::string("Error: ") + e.what();
            }
        }

        else if (action == InteractionEngine::ACCION_2) { // Action: Flip Stockpile
            Board* next = g->clone();
            try {
                ((GolfBoard*)next)->flipStockCard();
                app.changeState(GameState(next));
            }
            catch (const std::runtime_error& e) {
                delete next;
                message = std::string("Error: ") + e.what();
            }
        }

        else if (action == InteractionEngine::DESHACER) { // Deshacer
            try { 
                app.goToPast(); 
            }
            catch (const std::runtime_error& e) {
                message = std::string("Error: ") + e.what();
            }
        }

        else if (action == InteractionEngine::REHACER) { // Rehacer
            try {
                app.goToFuture();
            }
            catch (const std::runtime_error& e) {
                message = std::string("Error: ") + e.what();
            }
        }

        else if (action == InteractionEngine::ABANDONAR) { // Abandonar
            if (ie->confirmAbandon()) g->abandon();
        }
    } // End of Golf game loop

    // Show game results 
    GolfBoard* g = (GolfBoard*)app.getCurrent();
    ie->showMessage("Juego terminado. Puntaje final: " + 
        std::to_string(g->getTotalScore()) + " (" + g->getRating() + ")");
}








// ======================================================================
// 
// Spider solitaire execution
// 
// ======================================================================

void playSpider() {

    // Variables set up 
    InteractionEngine* ie = InteractionEngine::getInstance();
    Renderer* re = Renderer::getInstance();
    Application app(GameState(new SpiderBoard()));
    std::string message = "";


    while (true) { // Start of Spider game loop
        SpiderBoard* s = (SpiderBoard*)app.getCurrent(); // Get game state

        if (s->isGameWon()) { // Check for victory
            re->showSpider(s);
            ie->showMessage("¡Victoria! Completó las 8 escaleras.");
            break;
        }

        re->clearScreen(); // Clear console
        re->showSpider(s); // Display on console
        if (message.size() > 0) { // If there are messages, display them
            ie->showMessage(message);
            message = "";
        }

        int action = ie->selectAction(InteractionEngine::SPIDER); // Get user input


        // User actions decision tree
        if (action == InteractionEngine::ACCION_1) { // Action: Move cards
            int origin, dest, amount;
            ie->selectMove(origin, dest, amount);
            Board* next = s->clone();
            try {
                bool completed = ((SpiderBoard*)next)->changeColumn(origin, dest, amount);
                app.changeState(GameState(next));
                if (completed)
                    message = "¡Completó una escalera!";
            }
            catch (const std::runtime_error& e) {
                delete next;
                message = std::string("Error: ") + e.what();
            }
        }

        else if (action == InteractionEngine::ACCION_2) { // Action: Deal row
            Board* next = s->clone();
            try {
                int runs = ((SpiderBoard*)next)->dealRow();
                app.changeState(GameState(next));
                if (runs > 0)
                    message = "¡Completó una escalera!";
            }
            catch (const std::runtime_error& e) {
                delete next;
                message = std::string("Error: ") + e.what();
            }
        }

        else if (action == InteractionEngine::DESHACER) { // Deshacer
            try {
                app.goToPast();
            }
            catch (const std::runtime_error& e) {
                message = std::string("Error: ") + e.what();
            }
        }

        else if (action == InteractionEngine::REHACER) { // Rehacer
            try {
                app.goToFuture();
            }
            catch (const std::runtime_error& e) {
                message = std::string("Error: ") + e.what();
            }
        }

        else if (action == InteractionEngine::ABANDONAR) { // Abandonar
            if (ie->confirmAbandon()) {
                ie->showMessage("Derrota: abandonó la partida.");
                break;
            }
        }
    } // End of Spider game loop
}

int menu() {
    InteractionEngine* ie = InteractionEngine::getInstance();

    int mode = 0;

    while (true) {
        mode = ie->selectGameMode();
        if (mode == 1) {
            playGolf();
        }
        else if (mode == 2) {
            playSpider();
        }
        else {
            return 0;
        }
        if (!ie->selectPlayAgain())
            return 0;
    }
    return 0;
}




// ======================================================================
//
// main() method call
//
// ======================================================================

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    srand((unsigned int)time(0));
    Renderer::getInstance()->setAdvancedUI(ADVANCED_UI);

    int resultado = 0;

    if (RUN_TESTS) {
        std::cout << "Iniciando pruebas...\n";
        resultado += pruebas();
        std::cout << "Pruebas finalizadas.\n";
    } 
    else if (RUN_MAIN) {
        resultado += menu();
    }
    

     return resultado;
}

