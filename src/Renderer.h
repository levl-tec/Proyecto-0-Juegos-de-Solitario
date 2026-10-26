#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include "Card.h"
#include "GolfBoard.h"
#include "SpiderBoard.h"


class Renderer
{
private:
	bool advancedUI = false;

	Renderer() {}

public:

	static Renderer* getInstance() {
		static Renderer instance;
		return &instance;
	}

	void setAdvancedUI(bool advancedUI) {
		this->advancedUI = advancedUI;
	}

	std::string suitSymbol(char suit) {
		if (suit == 'S') return "♠";
		else if (suit == 'H') return "♥";
		else if (suit == 'D') return "♦";
		else return "♣";
	}

	std::string cardText(Card c) {
		if (!c.isVisible()) return "##";
		std::string value;
		int v = c.getValue();
		if (v == 1)
			value = "A";
		else if (v == 11)
			value = "J";
		else if (v == 12)
			value = "Q";
		else if (v == 13)
			value = "K";
		else
			value = std::to_string(v);
		return value + suitSymbol(c.getSuit());
	}

	void showCard(Card c) {
		std::cout << cardText(c) << " ";
	}

	// Counts characters on screen, not bytes. In UTF-8, the extra
	// bytes of a symbol always start with the bits 10xxxxxx.
	int displayWidth(std::string t) {
		int count = 0;
		for (int i = 0; i < (int)t.size(); i++)
			if ((t[i] & 0xC0) != 0x80) count++;
		return count;
	}

	void printPadded(std::string t, int width) {
		std::cout << t;
		for (int i = displayWidth(t); i < width; i++) std::cout << " ";
	}

	void showColumns(Column** cols, int count) {
		for (int c = 1; c <= count; c++) {
			printPadded("  " + std::to_string(c), 6);
		}
		std::cout << std::endl;

		int maxHeight = 0;
		for (int c = 0; c < count; c++) {
			if (cols[c]->getSize() > maxHeight) maxHeight = cols[c]->getSize();
		}

		for (int r = 0; r < maxHeight; r++) {
			for (int c = 0; c < count; c++) {
				if (r < cols[c]->getSize())
					printPadded("  " + cardText(cols[c]->getCard(r)), 6);
				else
					printPadded("", 6);
			}
			std::cout << std::endl;
		}
	}

	// How many cards at the bottom of the column can be moved together:
	// visible cards, each one exactly one value lower than the one above it
	int movableRun(Column* col) {
		int size = col->getSize();
		if (size == 0 || !col->getCard(size - 1).isVisible()) return 0;
		int count = 1;
		for (int r = size - 2; r >= 0; r--) {
			Card upper = col->getCard(r);
			Card lower = col->getCard(r + 1);
			if (!upper.isVisible() || upper.getValue() != lower.getValue() + 1) break;
			count++;
		}
		return count;
	}

	void showMovableRuns(Column** cols, int count) {
		for (int c = 0; c < count; c++) {
			printPadded("  (" + std::to_string(movableRun(cols[c])) + ")", 6);
		}
		std::cout << std::endl;
		std::cout << "(n) = cartas que se pueden mover juntas de esa columna" << std::endl;
	}

	void showGolf(GolfBoard* g) {
		if (advancedUI)
			showGolfAdvanced(g);
		else
			showGolfBasic(g);
	}

	void showSpider(SpiderBoard* s) {
		if (advancedUI)
			showSpiderAdvanced(s);
		else
			showSpiderBasic(s);
	}

	// TODO: UI avanzada con las cartas dibujadas (ver documents/reference/reference.txt).
	// Por ahora muestra un aviso y la UI basica.
	void showGolfAdvanced(GolfBoard* g) {
		std::cout << "[UI avanzada en construccion]" << std::endl;
		showGolfBasic(g);
	}

	void showSpiderAdvanced(SpiderBoard* s) {
		std::cout << "[UI avanzada en construccion]" << std::endl;
		showSpiderBasic(s);
	}

	void showGolfBasic(GolfBoard* g) {
		std::cout << "Ronda " << g->getRound() << " de 9 | Puntaje: " << g->getTotalScore() 
			<< " | Mazo: " << g->getStockSize() << " cartas" << std::endl;
		std::cout << "Descarte: ";
		showCard(g->getDiscardTop());
		std::cout << std::endl;

		Column* cols[7];
		for (int c = 1; c <= 7; c++) cols[c - 1] = g->getColumn(c);
		showColumns(cols, 7);

	}

	void showSpiderBasic(SpiderBoard* s) {
		std::cout << "Repartos restantes: " << s->getDealsLeft() << " | Escaleras completadas: "
			<< s->getCompletedRuns() << " de 8" << std::endl;

		Column* cols[10];
		for (int c = 1; c <= 10; c++) cols[c - 1] = s->getColumn(c);
		showColumns(cols, 10);
		showMovableRuns(cols, 10);
	}

	
	void clearScreen() { system("cls"); }

};

