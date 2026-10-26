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

	// ---------------------------------------------------------------
	// Advanced UI: cards drawn like in documents/reference/reference.txt
	// Every card is 10 characters wide and 7 lines tall, and is drawn
	// one line at a time so several columns can be printed side by side.
	// ---------------------------------------------------------------

	std::string repeat(std::string piece, int amount) {
		std::string result = "";
		for (int i = 0; i < amount; i++) result += piece;
		return result;
	}

	// Top line of a face up card, also used when another card covers it
	std::string cardTop(Card c) {
		std::string text = cardText(c);
		return "┌ " + text + " " + repeat("─", 6 - displayWidth(text)) + "┒";
	}

	// Line 'row' (0 to 6) of a face up card
	std::string cardLine(Card c, int row) {
		std::string text = cardText(c);
		if (row == 0) return cardTop(c);
		if (row == 3) return "│   " + suitSymbol(c.getSuit()) + "    ┃";
		if (row == 5) return "│" + repeat(" ", 8 - displayWidth(text)) + text + "┃";
		if (row == 6) return "┕━━━━━━━━┛";
		return "│        ┃";
	}

	// Line 'row' of a face down card
	std::string backLine(int row) {
		if (row == 0) return "┌────────┒";
		if (row == 2 || row == 4) return "│ X XX X ┃";
		if (row == 6) return "┕━━━━━━━━┛";
		return "│  X  X  ┃";
	}

	// Line 'row' of an empty spot
	std::string emptyLine(int row) {
		if (row == 0) return "╔═ ═ ═ ═ ╗";
		if (row == 2 || row == 4) return "║        ║";
		if (row == 6) return "╚ ═ ═ ═ ═╝";
		return "          ";
	}

	// Line 'row' of a pile seen from above. 'extra' adds edges on the right
	// so the pile looks thicker when it has more cards.
	std::string stockLine(int row, int extra) {
		std::string edge = "┃";
		if (row == 0) edge = "┒";
		if (row == 6) edge = "┛";
		return backLine(row) + repeat(edge, extra);
	}

	// Line 'row' of a column where the cards overlap: every card except
	// the last one only shows its top line
	std::string columnLine(Column* col, int row) {
		int size = col->getSize();
		if (size == 0) {
			if (row < 7) return emptyLine(row);
			return "          ";
		}
		if (row < size - 1) {
			Card c = col->getCard(row);
			if (c.isVisible()) return cardTop(c);
			return backLine(0);
		}
		int lastRow = row - (size - 1);
		if (lastRow < 7) {
			Card c = col->getCard(size - 1);
			if (c.isVisible()) return cardLine(c, lastRow);
			return backLine(lastRow);
		}
		return "          ";
	}

	// Number shown to the left of a card in Spider: how many cards would be
	// moved starting from that card (the amount the player has to type).
	// Only cards that can actually be moved get a number.
	std::string amountLabel(Column* col, int row, bool amounts) {
		int size = col->getSize();
		if (!amounts || row >= size) return "  ";
		int fromBottom = size - row;
		if (fromBottom > movableRun(col)) return "  ";
		std::string label = std::to_string(fromBottom);
		if (label.size() == 1) label += " ";
		return label;
	}

	// Prints the columns side by side, each one 12 characters wide
	// (2 for the amount number + 10 for the card)
	void showCascade(Column** cols, int count, bool amounts) {
		for (int c = 1; c <= count; c++) {
			std::string label = "[" + std::to_string(c) + "]";
			int left = 2 + (10 - (int)label.size()) / 2;
			std::cout << repeat(" ", left);
			printPadded(label, 12 - left);
		}
		std::cout << std::endl;

		int maxHeight = 0;
		for (int c = 0; c < count; c++) {
			int height = 7;
			if (cols[c]->getSize() > 0) height = cols[c]->getSize() - 1 + 7;
			if (height > maxHeight) maxHeight = height;
		}

		for (int r = 0; r < maxHeight; r++) {
			for (int c = 0; c < count; c++) {
				std::cout << amountLabel(cols[c], r, amounts);
				std::cout << columnLine(cols[c], r);
			}
			std::cout << std::endl;
		}
	}

	void showGolfAdvanced(GolfBoard* g) {
		std::cout << std::endl;
		std::cout << "  Ronda: [ " << g->getRound() << " de 9 ]     Puntaje: [ "
			<< g->getTotalScore() << " ]" << std::endl << std::endl;

		Column* cols[7];
		for (int c = 1; c <= 7; c++) cols[c - 1] = g->getColumn(c);
		showCascade(cols, 7, false);
		std::cout << std::endl;

		// Stock and discard pile
		int stock = g->getStockSize();
		int extra = 0;
		if (stock > 0) extra = (stock - 1) / 6;
		for (int r = 0; r < 7; r++) {
			if (r == 3)
				printPadded("  [" + std::to_string(stock) + " cartas restantes]", 26);
			else
				printPadded("", 26);

			if (stock > 0)
				printPadded(stockLine(r, extra), 16);
			else
				printPadded(emptyLine(r), 16);

			std::cout << cardLine(g->getDiscardTop(), r) << std::endl;
		}
		std::cout << repeat(" ", 29) << "Mazo" << repeat(" ", 10) << "Descarte" << std::endl;
	}

	void showSpiderAdvanced(SpiderBoard* s) {
		std::cout << std::endl;
		std::cout << "  Repartos restantes: [ " << s->getDealsLeft() << " ]     Escaleras completadas: [ "
			<< s->getCompletedRuns() << " de 8 ]" << std::endl << std::endl;

		// Top row: stock and the 8 completed runs (a finished run shows its K)
		int deals = s->getDealsLeft();
		Card king('S', 13, true);
		for (int r = 0; r < 7; r++) {
			std::cout << "  ";
			if (deals > 0)
				printPadded(stockLine(r, deals - 1), 22);
			else
				printPadded(emptyLine(r), 22);

			for (int i = 0; i < 8; i++) {
				std::cout << "  ";
				if (i < s->getCompletedRuns())
					std::cout << cardLine(king, r);
				else
					std::cout << emptyLine(r);
			}
			std::cout << std::endl;
		}
		std::cout << "     Mazo" << repeat(" ", 18) << "Escaleras completadas" << std::endl << std::endl;

		Column* cols[10];
		for (int c = 1; c <= 10; c++) cols[c - 1] = s->getColumn(c);
		showCascade(cols, 10, true);
		std::cout << "El numero junto a una carta es la cantidad a mover desde esa carta." << std::endl;
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

