#include <iostream>
#include <windows.h>
#include <cstdlib>
#include "Board.h"
#include "Card.h"
#include "DLinkedList.h"
#include "ArrayStack.h"
#include "GameState.h"
#include "GolfBoard.h"
#include "SpiderBoard.h"
#include "Column.h"
#include "InteractionEngine.h"



int pruebas()
{
    std::cout << "Entre a pruebas()" << std::endl;
    char* ranks = new char [4] {'S', 'C', 'H', 'D'};
    Column stockpile = Column();
    srand(time(0));
    for (int i = 0; i < 4; i++) {
        List<Card>* cardSecuence = new ArrayList<Card>(13);
        for (int j = 1; j < 14; j++) {
            Card card = Card(ranks[i], j, 1);
            cardSecuence->append(card);
        }

        std::cout << "Mezclando Palo" << std::endl;
        int size = cardSecuence->getSize();
        while (size != 0) {
            std::cout << size << std::endl;
            int num = rand() % cardSecuence->getSize();
            std::cout << "Creando Numero aleatorio" << std::endl;
            cardSecuence->goToPos(num);
            std::cout << "Yendo al numero" << std::endl;
            Card card = cardSecuence->remove();
            std::cout << "Saque la carta" << std::endl;
            stockpile.addCard(card);
            std::cout << "Agregue la carta" << std::endl;
            size = cardSecuence->getSize();
            std::cout << size << std::endl;
        }
    }

    std::cout << "Se creo el stockpile" << std::endl;
    
    List<Column*>* board = new ArrayList<Column*>(7);
    for (int j = 0; j < 7; j++) {
        std::cout << "Creando columna" << std::endl;
        List<Card>* columnCards = new DLinkedList<Card>();
        for (int k = 0; k < 5; k++) {
            columnCards->append(stockpile.removeCard());
        }
        Column* column = new Column(columnCards);
        board->append(column);
    }
    
     std::cout << "Se creo el board" << std::endl;

    Column discardpile;
    discardpile.addCard(stockpile.removeCard());

    std::cout << "Antes de crear el GolfBoard" << std::endl;

    Board* golf = new GolfBoard(stockpile, discardpile, board);

    std::cout << "Se creo el golfboard correctamente" << std::endl;

    Column descartePrueba;
    descartePrueba.addCard(Card('S', 7, true));

    List<Column*>* columnasPrueba = new ArrayList<Column*>(7);

    GolfBoard golfPrueba(Column(), descartePrueba, columnasPrueba);

    if (golfPrueba.isValidDiscard(Card('H', 6, true))) {
        std::cout << "Bien: 6 sobre 7 es valido" << std::endl;
    }
    else {
        std::cout << "ERROR: 6 sobre 7 deberia ser valido" << std::endl;
    }

    if (golfPrueba.isValidDiscard(Card('H', 8, true))) {
        std::cout << "Bien: 8 sobre 7 es valido" << std::endl;
    }
    else {
        std::cout << "ERROR: 8 sobre 7 deberia ser valido" << std::endl;
    }

    if (!golfPrueba.isValidDiscard(Card('H', 10, true))) {
        std::cout << "Bien: 10 sobre 7 es invalido" << std::endl;
    }
    else {
        std::cout << "ERROR: 10 sobre 7 no deberia ser valido" << std::endl;
    }


    List<Column*>* columnasGolf = new ArrayList<Column*>(7);

    for (int i = 0; i < 7; i++) {
        columnasGolf->append(new Column());
    }

    columnasGolf->goToPos(0);
    columnasGolf->getElement()->addCard(Card('H', 6, true));

    columnasGolf->goToPos(1);
    columnasGolf->getElement()->addCard(Card('S', 10, true));

    Column descarteGolf;
    descarteGolf.addCard(Card('S', 7, true));

    Column mazoGolf;

    GolfBoard golfDescartes(mazoGolf, descarteGolf, columnasGolf);

    golfDescartes.discardCard(0);

    columnasGolf->goToPos(0);

    if (columnasGolf->getElement()->getSize() == 0 &&
        descarteGolf.getSize() == 2) {
        std::cout << "Bien: discardCard movio la carta valida" << std::endl;
    }
    else {
        std::cout << "ERROR: discardCard no movio correctamente" << std::endl;
    }

    golfDescartes.discardCard(1);

    columnasGolf->goToPos(1);

    if (columnasGolf->getElement()->getSize() == 1 &&
        descarteGolf.getSize() == 2) {
        std::cout << "Bien: discardCard rechazo la carta invalida" << std::endl;
    }
    else {
        std::cout << "ERROR: discardCard permitio una carta invalida" << std::endl;
    }

    Column descarteRey;
    descarteRey.addCard(Card('S', 13, true));

    GolfBoard golfRey(Column(), descarteRey,
        new ArrayList<Column*>(7));

    if (golfRey.isValidDiscard(Card('H', 1, true))) {
        std::cout << "Bien: As sobre Rey es valido" << std::endl;
    }
    else {
        std::cout << "ERROR: As sobre Rey deberia ser valido" << std::endl;
    }

    Column descarteAs;
    descarteAs.addCard(Card('S', 1, true));

    GolfBoard golfAs(Column(), descarteAs,
        new ArrayList<Column*>(7));

    if (golfAs.isValidDiscard(Card('H', 13, true))) {
        std::cout << "Bien: Rey sobre As es valido" << std::endl;
    }
    else {
        std::cout << "ERROR: Rey sobre As deberia ser valido" << std::endl;
    }

    if (!golfAs.isValidDiscard(Card('H', 1, true))) {
        std::cout << "Bien: As sobre As es invalido" << std::endl;
    }
    else {
        std::cout << "ERROR: As sobre As no deberia ser valido" << std::endl;
    }

    List<Column*>* columnasPuntos = new ArrayList<Column*>(7);

    for (int i = 0; i < 7; i++) {
        Column* columna = new Column();

        for (int j = 0; j < i + 1; j++) {
            columna->addCard(Card('H', 5, true));
        }

        columnasPuntos->append(columna);
    }

    columnasPuntos->goToPos(0);

    Column mazoPuntos;
    Column descartePuntos;
    descartePuntos.addCard(Card('S', 7, true));

    GolfBoard golfPuntos(mazoPuntos, descartePuntos, columnasPuntos);

    std::cout << "Iniciando prueba de puntos de Golf" << std::endl;
    golfPuntos.nextRound();
    std::cout << "Termino prueba de puntos de Golf" << std::endl;

    List<Column*>* columnasMazo = new ArrayList<Column*>(7);

    for (int i = 0; i < 7; i++) {
        Column* columna = new Column();
        columna->addCard(Card('H', 5, true));
        columnasMazo->append(columna);
    }

    columnasMazo->goToPos(0);

    Column mazoConCartas;
    mazoConCartas.addCard(Card('S', 2, true));
    mazoConCartas.addCard(Card('S', 3, true));
    mazoConCartas.addCard(Card('S', 4, true));

    Column descarteConMazo;
    descarteConMazo.addCard(Card('S', 7, true));

    GolfBoard golfConMazo(mazoConCartas, descarteConMazo,
        columnasMazo);

    std::cout << "Iniciando prueba de puntaje con mazo" << std::endl;

    golfConMazo.nextRound();

    std::cout << "Termino prueba de puntaje con mazo" << std::endl;

    List<Column*>* columnasA = new ArrayList<Column*>(7);
    List<Column*>* columnasB = new ArrayList<Column*>(7);

    for (int i = 0; i < 7; i++) {
        Column* columnaA = new Column();
        columnaA->addCard(Card('H', 5, true));
        columnasA->append(columnaA);

        Column* columnaB = new Column();
        columnaB->addCard(Card('S', 3, true));
        columnaB->addCard(Card('S', 4, true));
        columnasB->append(columnaB);
    }

    columnasA->goToPos(0);
    columnasB->goToPos(0);

    Column mazoA;
    Column mazoB;

    Column descarteA;
    Column descarteB;

    descarteA.addCard(Card('H', 7, true));
    descarteB.addCard(Card('S', 8, true));

    GolfBoard golfA(mazoA, descarteA, columnasA);
    GolfBoard golfB(mazoB, descarteB, columnasB);

    std::cout << "Iniciando prueba de independencia" << std::endl;

    golfA.nextRound();

    golfB.nextRound();
    golfB.nextRound();

    std::cout << "Revisar golfA y golfB en el depurador" << std::endl;

    std::cout << "Termino prueba de independencia" << std::endl;

    Column stockpile2 = Column();

    for (int i = 0; i < 8; i++) {
        List<Card>* cardSecuence = new ArrayList<Card>(13);
        for (int j = 1; j < 14; j++) {
            Card card = Card(ranks[1], j, 1);
            cardSecuence->append(card);
        }

        std::cout << "Mezclando Palo" << std::endl;
        int size = cardSecuence->getSize();
        while (size != 0) {
            std::cout << size << std::endl;
            int num = rand() % cardSecuence->getSize();
            std::cout << "Creando Numero aleatorio" << std::endl;
            cardSecuence->goToPos(num);
            std::cout << "Yendo al numero" << std::endl;
            Card card = cardSecuence->remove();
            std::cout << "Saque la carta" << std::endl;
            stockpile2.addCard(card);
            std::cout << "Agregue la carta" << std::endl;
            size = cardSecuence->getSize();
            std::cout << size << std::endl;
        }
    }

     List<Column*>* board2 = new ArrayList<Column*>(10);
    for (int j = 0; j < 10; j++) {
        std::cout << "Creando columnas" << std::endl;
        List<Card>* columnCards = new DLinkedList<Card>();
        if (j < 4) {
            for (int k = 0; k < 6; k++) {
            Card card = stockpile2.removeCard();
            if (k != 5)
                card.setVisibility(0);
            columnCards->append(card);
            }
        }
        else {
            for (int k = 0; k < 5; k++) {
                Card card = stockpile2.removeCard();
                if (k != 4)
                    card.setVisibility(0);
                columnCards->append(card);
            }
        }
        Column* column = new Column(columnCards);
        board2->append(column);
    }
    
     std::cout << "Se creo el board" << std::endl;

     std::cout << "Cartas restantes de Spider: "
         << stockpile2.getSize() << std::endl;

     if (stockpile2.getSize() == 50) {
         std::cout << "Bien, reparto correcto" << std::endl;
     }
     else {
         std::cout << "ERROR: Reparto incorrecto" << std::endl;
     }

    Board* spider = new SpiderBoard(stockpile2, board2);

    List<Column*>* columnasSpiderPrueba = new ArrayList<Column*>(10);

    for (int i = 0; i < 10; i++) {
        columnasSpiderPrueba->append(new Column());
    }

    columnasSpiderPrueba->goToPos(0);
    Column* origenSpider = columnasSpiderPrueba->getElement();
    origenSpider->addCard(Card('C', 8, true));

    columnasSpiderPrueba->goToPos(1);
    Column* destinoSpider = columnasSpiderPrueba->getElement();
    destinoSpider->addCard(Card('C', 9, true));

    SpiderBoard spiderPrueba(Column(), columnasSpiderPrueba);

    std::cout << "Iniciando prueba de movimiento Spider" << std::endl;

    try {
        spiderPrueba.changeColumn(0, 1, 1);

        std::cout << "Movimiento ejecutado" << std::endl;
    }
    catch (const std::exception& error) {
        std::cout << "Excepcion en movimiento valido: "
            << error.what() << std::endl;
    }

    std::cout << "Cartas origen: "
        << origenSpider->getSize() << std::endl;

    std::cout << "Cartas destino: "
        << destinoSpider->getSize() << std::endl;

    if (origenSpider->getSize() == 0 &&
        destinoSpider->getSize() == 2) {
        std::cout << "Bien: Movimiento Spider correcto" << std::endl;
    }
    else {
        std::cout << "ERROR: Movimiento Spider incorrecto" << std::endl;
    }


    Column destinoSecuencia;
    destinoSecuencia.addCard(Card('C', 9, true));

    List<Card>* secuenciaPrueba = new ArrayList<Card>(2);
    secuenciaPrueba->append(Card('C', 9, true));
    secuenciaPrueba->append(Card('C', 8, true));

    bool movimientoRechazado = false;

    try {
        destinoSecuencia.isValidColumnMove(secuenciaPrueba);
    }
    catch (const std::exception& error) {
        movimientoRechazado = true;
        std::cout << "Movimiento rechazado: "
            << error.what() << std::endl;
    }

    if (movimientoRechazado) {
        std::cout << "Bien: Spider rechazo la secuencia invalida"
            << std::endl;
    }
    else {
        std::cout << "ERROR: Spider acepto una secuencia invalida"
            << std::endl;
    }

    Column destinoUnaCarta;
    destinoUnaCarta.addCard(Card('C', 9, true));

    List<Card>* cartaParaMover = new ArrayList<Card>(1);
    cartaParaMover->append(Card('C', 8, true));

    bool cartaAceptada = true;

    try {
        destinoUnaCarta.isValidColumnMove(cartaParaMover);
    }
    catch (const std::exception& error) {
        cartaAceptada = false;
        std::cout << "Excepcion con carta valida: "
            << error.what() << std::endl;
    }

    if (cartaAceptada) {
        std::cout << "Bien: Spider acepta 8 sobre 9"
            << std::endl;
    }
    else {
        std::cout << "ERROR: Spider rechaza 8 sobre 9"
            << std::endl;
    }

    Column columnaVacia;

    List<Card>* secuenciaVacia = new ArrayList<Card>(2);
    secuenciaVacia->append(Card('C', 9, true));
    secuenciaVacia->append(Card('C', 8, true));

    bool aceptaColumnaVacia = true;

    try {
        columnaVacia.isValidColumnMove(secuenciaVacia);
    }
    catch (const std::exception& error) {
        aceptaColumnaVacia = false;
        std::cout << "Excepcion con columna vacia: "
            << error.what() << std::endl;
    }

    if (aceptaColumnaVacia) {
        std::cout << "Bien: Spider permite mover a columna vacia"
            << std::endl;
    }
    else {
        std::cout << "ERROR: Spider rechaza columna vacia"
            << std::endl;
    }

    std::cout << "Iniciando prueba de InteractionEngine" << std::endl;

    int modoElegido = InteractionEngine::getInstance()->selectGameMode();

    if (modoElegido == 2) {
        std::cout << "Bien: InteractionEngine selecciono Spider" << std::endl;
    }
    else {
        std::cout << "ERROR: InteractionEngine devolvio otra opcion" << std::endl;
    }

    std::cout << "Iniciando prueba de columnas Golf"
        << std::endl;

    int columnaElegida =
        InteractionEngine::getInstance()->selectColumn(7);

    if (columnaElegida == 7) {
        std::cout << "Bien: Seleccion de columna correcta"
            << std::endl;
    }
    else {
        std::cout << "ERROR: Seleccion de columna incorrecta"
            << std::endl;
    }

    std::cout << "Iniciando prueba de selectMove Spider"
        << std::endl;

    int origen = 0;
    int destino = 0;
    int cantidad = 0;

    InteractionEngine::getInstance()->selectMove(
        origen, destino, cantidad
    );


    if (origen == 3 && destino == 5 && cantidad == 2) {
        std::cout << "Bien: selectMove recibio los tres valores"
            << std::endl;
    }
    else {
        std::cout << "ERROR: selectMove devolvio valores incorrectos"
            << std::endl;
    }

    {
        std::cout << "Iniciando prueba de abandono"
            << std::endl;

        bool abandonarSi =
            InteractionEngine::getInstance()->confirmAbandon();

        bool abandonarNo =
            InteractionEngine::getInstance()->confirmAbandon();

        if (abandonarSi == true && abandonarNo == false) {
            std::cout << "Bien: Confirmacion de abandono correcta"
                << std::endl;
        }
        else {
            std::cout << "ERROR: Confirmacion de abandono incorrecta"
                << std::endl;
        }
    }

    {
        std::cout << "Iniciando prueba de volver al menu"
            << std::endl;

        bool volverMenu =
            InteractionEngine::getInstance()->selectPlayAgain();

        bool salirPrograma =
            InteractionEngine::getInstance()->selectPlayAgain();

        if (volverMenu == true && salirPrograma == false) {
            std::cout << "Bien: selectPlayAgain funciona correctamente"
                << std::endl;
        }
        else {
            std::cout << "ERROR: selectPlayAgain devolvio valores incorrectos"
                << std::endl;
        }
    }

    {
        std::cout << "Iniciando prueba de acciones Golf"
            << std::endl;

        int accionGolf =
            InteractionEngine::getInstance()->selectAction(1);

        if (accionGolf == 1) {
            std::cout << "Bien: Accion Golf correcta" << std::endl;
        }
        else {
            std::cout << "ERROR: Accion Golf incorrecta" << std::endl;
        }

        std::cout << "Iniciando prueba de acciones Spider"
            << std::endl;

        int accionSpider =
            InteractionEngine::getInstance()->selectAction(2);

        if (accionSpider == 2) {
            std::cout << "Bien: Accion Spider correcta" << std::endl;
        }
        else {
            std::cout << "ERROR: Accion Spider incorrecta" << std::endl;
        }
    }

    std::cout << "Saliendo de pruebas" << std::endl;

    return 0;
}
