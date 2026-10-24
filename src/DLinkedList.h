#pragma once

#include "List.h"
#include "DNode.h"
#include "ArrayList.h"
#include <iostream>
#include <stdexcept>

template <typename E>
class DLinkedList : public List<E> {
private:
	DNode<E>* head;
	DNode<E>* tail;
	DNode<E>* current;
	int size;

public:
	DLinkedList() {
		current = head = new DNode<E>(nullptr, nullptr);
		head->next = tail = new DNode<E>(nullptr, head);
		size = 0;
	}
	~DLinkedList() {
		clear();
		delete head;
		delete tail;
	}

	void insert(E element) {
		current->next = current->next->previous = new DNode<E>(element, current->next, current);
		size++;
	}

	void append(E element) {
		tail->previous = tail->previous->next = new DNode(element, tail, tail->previous);
		size++;
	}

	void setElement(E element) {
		if (size == 0) 
			throw std::runtime_error("List is empty");
		if (current->next == tail) 
			throw std::runtime_error("No current element");
		current->next->element = element;
	}

	E remove() {
		if (size == 0) 
			throw std::runtime_error("List is empty");
		if (current->next == tail) 
			throw std::runtime_error("No current element");
		E elemento = current->next->element;
		current->next = current->next->next;
		delete current->next->previous;
		current->next->previous = current;
		size--;
		return elemento;
	}

	void clear() {
		while (head->next != tail) {
			head->next = head->next->next;
			delete head->next->previous;
		}
		current = tail->previous = head;
		size = 0;
	}

	E getElement() {
		return current->next->element;
	}

	void goToStart() {
		current = head;
	}

	void goToEnd() {
		current = tail->previous;
	}

	void goToPos(int pos) {
		if (pos < 0 || pos > size)
			throw std::runtime_error("Error: invalid position.");
		if (pos <= size / 2) {
			current = head;
			for (int i = 0; i < pos; i++)
				current = current->next;
		}
		else {
			current = tail->previous;
			for (int i = 0; i < size - pos; i++)
				current = current->previous;
		}
	}

	void next() {
		if (current != tail->previous)
			current = current->next;
	}

	void previous() {
		if (current != head)
			current = current->previous;
	}

	bool atEnd() {
		return current->next == tail;
	}

	bool atStart() {
		return current == head;
	}

	int getPos() {
		DNode<E>* temp = head;
		int pos = 0;
		while (temp != current) {
			temp = temp->next;
			pos++;
		}
		return pos;
	}

	List<E>* slice(int start, int end) {
		if (start == 0 && end == size - 1)
			return this;
		this->goToPos(start);
		List<E>* listSlice = new ArrayList<E>(end-start);
		for (int i = 0; i<listSlice.getSize(); i++) {
			listSlice->append(this->getElement());
			this->next();
		}
		return listSlice;
	}

	int getSize() {
		return size;
	}

	void print() {
		std::cout << "[";
		DNode<E>* temp = head->next;
		while (temp != tail) {
			std::cout << temp->element;
			if (temp != tail->previous)
				std::cout << ", ";
			temp = temp->next;
		}
		std::cout << "]" << '\n';
	}

};