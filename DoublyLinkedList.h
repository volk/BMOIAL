#ifndef _DOUBLYLINKEDLIST_H
#define _DOUBLYLINKEDLIST_H

#include <iostream>
#include <string>
#include <cstdlib>
#include "Node.h"

class DoublyLinkedList {

	public:
		DoublyLinkedList();
		~DoublyLinkedList();
		bool empty();
		Node* firstRight();
		Node* firstLeft();
		Node* nextRight(Node* n);
		Node* nextLeft(Node* n);
		void insertRight(int n);
		void insertLeft(int n);
		void insertRight(Node* n);
		void insertLeft(Node* n);
		int size();
		bool isFirst(Node* n);
		bool isLast(Node* n);

	protected:
		Node* leftTail;
		Node* rightTail;
		int length;
};

#endif 
