#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdio>
#include <string>
#include "Column.h"
#include "Card.h"
#include "DLinkedList.h"
#include "ArrayStack.h"
#include "GameState.h"

int pruebas();

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

int main()
{
    std::cout << "Iniciando pruebas...\n";
    // SetConsoleOutputCP(CP_UTF8);
    // SetConsoleCP(CP_UTF8);
    // int result = 0;
    
    // result += basicTest();
    // result += getConsoleProps();
    // result += resizeTest();
    // result += renderingTest();

    int resultado = pruebas();
    std::cout << "Pruebas finalizadas.\n";

     return resultado;
}

