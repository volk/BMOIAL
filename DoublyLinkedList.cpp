#include <iostream>
#include <string>
#include <cstdlib>
#include "Node.h"
#include "DoublyLinkedList.h"


DoublyLinkedList::DoublyLinkedList() 
{
	leftTail = rightTail = NULL;
	length = 0;
}

DoublyLinkedList::~DoublyLinkedList() 
{
	Node *n, *d;

	if(size() != 0) {
		d = leftTail;

		while(d != NULL) {
			n = d->right();
			delete d;
			d = n;
			length--;
		}
	}

	if(length != 0) {
		std::cout << "~DoublyLinkedList fails length[" << length << "]" 
			<< std::endl;
	}

	length = 0;
}

bool DoublyLinkedList::empty() 
{
	//bug prevention
	return leftTail == NULL && rightTail == NULL;
}

Node* DoublyLinkedList::firstRight() 
{
	return rightTail;
}

Node* DoublyLinkedList::firstLeft() 
{
	return leftTail;
}

Node* DoublyLinkedList::nextRight(Node* n) 
{
	if(n == NULL) {
		return NULL;
	}

	return n->right();
}

Node* DoublyLinkedList::nextLeft(Node* n) 
{
	if(n == NULL) {
		return NULL;
	}

	return n->left();
}

void DoublyLinkedList::insertRight(int n) 
{
	insertRight(new Node(n));
}

void DoublyLinkedList::insertLeft(int n) 
{
	insertLeft(new Node(n));
}

void DoublyLinkedList::insertRight(Node* n) 
{
	if(n == NULL) {
		return;
	}

	length++;
	n->setLeft(rightTail);
	n->setRight(NULL);

	if(rightTail != NULL) {
		rightTail->setRight(n);
	}

	rightTail = n;

	if(size() == 1) {
		leftTail = n;
	}
}

void DoublyLinkedList::insertLeft(Node* n) 
{
	if(n == NULL) {
		return;
	}

	length++;

	n->setLeft(NULL);
	n->setRight(leftTail);

	if(leftTail != NULL) {
		leftTail->setLeft(n);
	}

	leftTail = n;

	if(size() == 1) {
		rightTail = n;
	}
}

int DoublyLinkedList::size() 
{
	return length;
}

bool DoublyLinkedList::isFirst(Node* n) 
{
	return n == leftTail;
}

bool DoublyLinkedList::isLast(Node* n) 
{
	return n == rightTail;
}
