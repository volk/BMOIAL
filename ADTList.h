#ifndef _LISTADT_H
#define _LISTADT_H

#include "DoublyLinkedList.h"
#include "Node.h"

class ADTList {

	public:
		ADTList();
		~ADTList();
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
		bool isLast(Node* n);
		bool isFirst(Node* n);

	protected:
		DoublyLinkedList* list;
};

#endif 
