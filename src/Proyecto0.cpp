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



// 
// SetConsoleCP(CP_UTF8);
// int result = 0;

// result += basicTest();
// result += getConsoleProps();
// result += resizeTest();
// result += renderingTest();


// static HANDLE out;

// void print(const std::wstring& s)
// {
//     DWORD written;
//     WriteConsoleW(out, s.c_str(), (DWORD)s.size(), &written, nullptr);
// }

// // Prints an empty frame using whatever border characters you pass in
// void frame(int w, int h,
//     wchar_t tl, wchar_t t, wchar_t tr,
//     wchar_t l, wchar_t r,
//     wchar_t bl, wchar_t b, wchar_t br)
// {
//     print(std::wstring(1, tl) + std::wstring(w - 2, t) + tr + L"\n");
//     for (int i = 0; i < h - 2; i++)
//         print(std::wstring(1, l) + std::wstring(w - 2, L' ') + r + L"\n");
//     print(std::wstring(1, bl) + std::wstring(w - 2, b) + br + L"\n");
// }

// int renderingTest() {
//     out = GetStdHandle(STD_OUTPUT_HANDLE);

//     print(L"Suits (every | should line up with the dots below):\n");
//     print(L"|\u2660|\u2665|\u2663|\u2666|\u2664|\u2661|\u2667|\u2662|\U0001F0A0|\n");
//     print(L"|.|.|.|.|.|.|.|.|.|\n\n");

//     print(L"Style 1 (light top/left, heavy bottom/right):\n");
//     frame(10, 5, L'\u250C', L'\u2500', L'\u2512',
//         L'\u2502', L'\u2503',
//         L'\u2515', L'\u2501', L'\u251B');

//     print(L"\nStyle 2 (light top/left, double bottom/right):\n");
//     frame(10, 5, L'\u250C', L'\u2500', L'\u2556',
//         L'\u2502', L'\u2551',
//         L'\u2558', L'\u2550', L'\u255D');

//     print(L"\nStyle 3 (all double):\n");
//     frame(10, 5, L'\u2554', L'\u2550', L'\u2557',
//         L'\u2551', L'\u2551',
//         L'\u255A', L'\u2550', L'\u255D');

//     print(L"\nPress Enter to exit...");
//     getchar();
//     return 0;
// }


// int getConsoleProps() {
//     // Get a handle to the standard output device (the console)
//     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

//     if (hConsole == INVALID_HANDLE_VALUE) {
//         std::cerr << "Failed to get console handle." << std::endl;
//         return 1;
//     }

//     // Structure to hold the console information
//     CONSOLE_SCREEN_BUFFER_INFO csbi;

//     // Call GetConsoleScreenBufferInfo to populate the structure
//     if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
//         // Calculate console width and height in character cells
//         int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
//         int consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

//         std::cout << "--- Console Screen Buffer Info ---" << std::endl;
//         std::cout << "Buffer Size (Cols x Rows): "
//             << csbi.dwSize.X << " x " << csbi.dwSize.Y << std::endl;
//         std::cout << "Window Size (Cols x Rows): "
//             << consoleWidth << " x " << consoleHeight << std::endl;
//         std::cout << "Cursor Position (X, Y):    "
//             << csbi.dwCursorPosition.X << ", " << csbi.dwCursorPosition.Y << std::endl;
//         std::cout << "Text Attributes (Color):   0x"
//             << std::hex << csbi.wAttributes << std::dec << std::endl;
//     }
//     else {
//         std::cerr << "GetConsoleScreenBufferInfo failed with error code: "
//             << GetLastError() << std::endl;
//         return 1;
//     }

//     return 0;
// }

// int resizeTest() {
//     HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
//     std::cout << "Resize the window, then press any key. Press q to quit.\n";

//     int count = 0;
//     while (true)
//     {
//         int key = _getch();
//         if (key == 'q' || key == 'Q') break;

//         CONSOLE_SCREEN_BUFFER_INFO info;
//         if (!GetConsoleScreenBufferInfo(h, &info))
//         {
//             std::cout << "GetConsoleScreenBufferInfo failed\n";
//             break;
//         }

//         int winW = info.srWindow.Right - info.srWindow.Left + 1;
//         int winH = info.srWindow.Bottom - info.srWindow.Top + 1;

//         std::cout << "#" << ++count
//             << "  buffer " << info.dwSize.X << "x" << info.dwSize.Y
//             << "  window " << winW << "x" << winH
//             << "  window top row " << info.srWindow.Top
//             << "\n";
//     }
//     return 0;
// }

// int basicTest() {
//     Card CardPrueba = Card('S', 1, 1);
//     Card CardPrueba2 = Card('H', 13, 1);
//     Card CardPrueba3 = Card('D', 2, 1);
//     Card CardPrueba4 = Card('C', 12, 1);
//     // std::cout << CardPrueba;
//     // std::cout << '\n' << '\n';
//     // std::cout << (CardPrueba.getValue() > CardPrueba2.getValue()) << '\n';

//     // std::cout << "Inicio pruebas pilasCards, mazo, GameState" << '\n';
//     List<Card>* Cards = new DLinkedList<Card>();
//     List<Card>* Cards2 = new DLinkedList<Card>();
//     Cards->append(CardPrueba);
//     Cards->append(CardPrueba2);
//     Cards2->append(CardPrueba3);
//     Cards2->append(CardPrueba4);
//     Column column = Column(Cards);
//     Column column2 = Column(Cards2);
//     List<Column>* pilasCards = new ArrayList<Column>(7);
//     pilasCards->append(column);
//     pilasCards->append(column2);
//     Stack<Card>* mazo = new ArrayStack<Card>();
//     return 0;
// }