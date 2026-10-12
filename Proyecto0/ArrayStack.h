#pragma once

#include <stdexcept>
#include "Stack.h"
#include "Includes.h"
#include <iostream>

template<typename E>

class ArrayStack : public Stack<E> {
private:
	E* elements;
	int max;
	int size;

public:
	ArrayStack(int max = DEFAULT_MAX) {
		if (max < 1)
			throw std::runtime_error("Tamaño maximo invalido");
		elements = new E[max];
		this->max = max;
		size = 0;
	}
	~ArrayStack() {
		delete[] elements;
	}
	void push(E element) {
		if (size == max)
			throw std::runtime_error("Stack overflow.");
		elements[size] = element;
		size++;
	}
	E pop() {
		if (size == 0)
			throw std::runtime_error("Stack empty.");
		size--;
		return elements[size];
	}
	E topValue() {
		if (size == 0)
			throw std::runtime_error("Stack empty.");
		return elements[size - 1];
	}
	void clear() {
		size = 0;
	}
	bool isEmpty() {
		return size == 0;
	}
	int getSize() {
		return size;
	}

	void print() {
		std::cout << "[";
		for (int i = size - 1; i >= 0; i--) {
			if (i > 0) { std::cout << elements[i] << ", "; }
			else { std::cout << elements[i]; }
		}
		std::cout << "]" << std::endl;
	}
};