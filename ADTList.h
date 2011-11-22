#ifndef _LISTADT_H
#define _LISTADT_H

#include "DoublyLinkedList.h"
#include "Node.h"

class ADTList {

	public:
		ADTList();
		~ADTList();
		//return true if list is empty
		bool empty();
		//returns the rightmost Node in the list
		Node* firstRight();
		//returns the leftmost Node in the list
		Node* firstLeft();
		//returns the Node to the right of node n
		Node* nextRight(Node* n);
		//returns the Node to the left of node n
		Node* nextLeft(Node* n);
		//inserts a new Node with the value n to the right end of the list
		void insertRight(int n);
		//inserts a new Node with the value n to the left end of the list
		void insertLeft(int n);
		//inserts a new Node to the right end of the list
		void insertRight(Node* n);
		//inserts a new Node to the left end of the list
		void insertLeft(Node* n);
		//returns the number of nodes in the list
		int size();
		//returns true if n is the rightmost Node in the list; false otherwise
		bool isLast(Node* n);
		//returns true if n is the leftmost Node in the list; false otherwise
		bool isFirst(Node* n);

	protected:
		DoublyLinkedList* list;
};

#endif 
