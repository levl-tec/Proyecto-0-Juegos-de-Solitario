#pragma once

#include <iostream>
#include "Card.h"
#include "GolfBoard.h"
#include "SpiderBoard.h"


class Renderer
{
private:
	Renderer() {}

public:

	static Renderer* getInstance() {
		static Renderer instance;
		return &instance;
	}
	
	void showCard(Card c) {
		if (!c.isVisible()) {
			std::cout << "## ";
			return;
		}
		int v = c.getValue();
		if (v == 1)
			std::cout << "A";
		else if (v == 11)
			std::cout << "J";
		else if (v == 12)
			std::cout << "Q";
		else if (v == 13)
			std::cout << "K";
		else
			std::cout << v;
		std::cout << c.getSuit() << " ";
	}

	void showGolf(GolfBoard* g) {
		std::cout << "Ronda " << g->getRound() << " de 9 | Puntaje: " << g->getTotalScore() 
			<< " | Mazo: " << g->getStockSize() << " cartas" << std::endl;
		std::cout << "Descarte: ";
		showCard(g->getDiscardTop());
		std::cout << std::endl;

		for (int c = 1; c < 8; c++) {
			Column* col = g->getColumn(c);
			std::cout << "Col " << c << ": ";

			int i = 0;
			while (i < col->getSize()) {
				showCard(col->getCard(i));
				i++;
			}
			std::cout << std::endl;

		}


	}

	void showSpider(SpiderBoard* s) {
		std::cout << "Repartos restantes: " << s->getDealsLeft() << " | Escaleras completadas: "
			<< s->getCompletedRuns() << " de 8" << std::endl;

		for (int c = 1; c < 11; c++) {
			Column* col = s->getColumn(c);
			std::cout << "Col " << c << ": ";

			int i = 0;
			while (i < col->getSize()) {
				showCard(col->getCard(i));
				i++;
			}
			std::cout << std::endl;

		}

	}

	

};

