#pragma once

#include <iostream>
#include <stdexcept>
#include "Stack.h"
#include "Node.h"

template <typename E>
class LinkedStack : public Stack<E>
{
private:
	Node<E>* top;
	int size;

public:
	LinkedStack()
	{
		top = nullptr;
		size = 0;
	}

	~LinkedStack()
	{
		clear();
	}

	void push(E element)
	{
		top = new Node<E>(element, top);
		size++;
	}

	E pop()
	{
		if (size == 0)
			throw std::runtime_error("Stack is empty");
		E result = top->element;
		Node<E>* temp = top->next;
		delete top;
		top = temp;
		size--;
		return result;
	}

	E topValue()
	{
		if (size == 0)
			throw std::runtime_error("Stack is empty");
		return top->element;
	}

	void clear()
	{
		Node<E>* temp;
		while (top != nullptr)
		{
			temp = top->next;
			delete top;
			top = temp;
		}
		size = 0;
	}

	bool isEmpty()
	{
		return size == 0;
	}

	int getSize()
	{
		return size;
	}

	void print()
	{
		if (size == 0)
			throw std::runtime_error("Stack is empty");
		std::cout << "[";
		Node<E> *temp = top;
		while (temp != nullptr)
		{
			std::cout << temp->element;
			if (temp->next != nullptr)
				std::cout << ", ";
			temp = temp->next;
		}
		std::cout << "]" << std::endl;
	}
};

