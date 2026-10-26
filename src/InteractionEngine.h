#ifndef INTERACTIONENGINE_H
#define INTERACTIONENGINE_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>

using std::cout;
using std::cin;
using std::getline;
using std::string;
using std::exit;
using std::to_string;
using std::runtime_error;



class InteractionEngine {
public:

	// Modos de juego
	static const int GOLF = 1;
	static const int SPIDER = 2;
	static const int SALIR = 3;

	// Acciones (iguales par los dos juegos)
	static const int ACCION_1 = 1;    
	static const int ACCION_2 = 2;   
	static const int DESHACER = 3;
	static const int REHACER = 4;
	static const int ABANDONAR = 5;

	static InteractionEngine* getInstance() {
		static InteractionEngine instance;
		return &instance;
	}

	//Menu Principal
	int selectGameMode() {
		cout << "\n=== JUEGOS DE SOLITARIO ===\n";
		cout << "1. Solitario Golf\n";
		cout << "2. Solitario Spider\n";
		cout << "3. Salir\n";
		return getRestrictedInteger("Elija una opcion", 1, 3);
	}

	//Menu de acciones
	int selectAction(int game) {
		cout << "\n--- Que desea hacer? ---\n";
		if (game == GOLF) {
			cout << "1. Elegir columna para descartar carta\n";
			cout << "2. Voltear carta del mazo\n";
		}
		else {
			cout << "1. Mover\n";
			cout << "2. Repartir\n";
		}
		cout << "3. Deshacer\n";
		cout << "4. Rehacer\n";
		cout << "5. Abandonar\n";
		return getRestrictedInteger("Elija una accion", 1, 5);
	}

	//Pide una columna entre 1 y maxColumnas (Golf: 7, Spider: 10)
	int selectColumn(int maxColumnas) {
		return getRestrictedInteger("Elija la columna", 1, maxColumnas);
	}

	//Spider: pide origen, destino y cantidad de cartas
	void selectMove(int& origen, int& destino, int& cantidad) {
		origen = getRestrictedInteger("Columna origen", 1, 10);
		destino = getRestrictedInteger("Columna destino", 1, 10);
		cantidad = getRestrictedInteger("Cantidad de cartas a mover", 1, 13);
	}

	//Pregunta si el usuario desea abandonar. Devuelve true si si.
	bool confirmAbandon() {
		cout << "\nSeguro que desea abandonar?\n";
		cout << "1. Si\n";
		cout << "2. No\n";
		return getRestrictedInteger("Elija una opcion", 1, 2) == 1;
	}

	//Pregunta si el usuario desea volver al menu principal. Devuelve true si si.
	bool selectPlayAgain() {
		cout << "\n1. Volver al menu principal\n";
		cout << "2. Salir por completo\n";
		return getRestrictedInteger("Elija una opcion", 1, 2) == 1;
	}
	
	//Espera que usuario presione ENTER para continuar 
	void pause() {
		cout << "Presione ENTER para continuar...";
		string basura;
		getline(cin, basura);
	}

	// Anuncia que va a empezar la siguiente ronda y espera ENTER
	void nextRound(int ronda) {
		cout << "\n=== RONDA " << ronda << " ===\n";
		pause();
	}

	// Muestra un mensaje 
	void showMessage(string message) {
		cout << message << "\n";
	}

	// Muestra un mensaje de error
	void showError(string message) {
		cout << "Error: " << message << "\n";
	}

private:
	InteractionEngine() {}

	// Pide un numero entre lowerBound y upperBound.
	// Si algo sale mal lanza un runtime_error, lo atrapa,
	// muestra el mensaje y vuelve a pedir el numero.
	int getRestrictedInteger(string message, int lowerBound, int upperBound) {
		while (true) {
			try {
				cout << message << " (" << lowerBound << "-" << upperBound << "): ";
				int numero;
				cin >> numero;
				if (cin.fail()) {
					if (cin.eof()) {
						std::cout << "Entrada finalizada. Saliendo...";
						std::exit(0);
					}
					cin.clear();
					cin.ignore(1000, '\n');
					throw runtime_error("Debe escribir un numero.");
				}
				cin.ignore(1000, '\n');

				if (numero < lowerBound || numero > upperBound) {
					throw runtime_error("El numero debe estar entre " + to_string(lowerBound) +
						" y " + to_string(upperBound) + ".");
				}
				return numero;
			}
			catch (const runtime_error& e) {
				showError(e.what());
			}
		}
	}

};
#endif
