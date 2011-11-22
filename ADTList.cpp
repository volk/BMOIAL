#include "DoublyLinkedList.h"
#include "Node.h"
#include "ADTList.h"

ADTList::ADTList() {
	list = new DoublyLinkedList();
}

ADTList::~ADTList() {
	delete list;
}

bool ADTList::empty() {
	return list->empty();
}

Node* ADTList::firstRight() {
	return list->firstRight();
}

Node* ADTList::firstLeft() {
	return list->firstLeft();
}

Node* ADTList::nextRight(Node* n) {
	return list->nextRight(n);
}

Node* ADTList::nextLeft(Node* n) {
	return list->nextLeft(n);
}

void ADTList::insertRight(int n) {
	list->insertRight(n);
}

void ADTList::insertLeft(int n) {
	list->insertLeft(n);
}

void ADTList::insertRight(Node* n) {
	list->insertRight(n);
}

void ADTList::insertLeft(Node* n) {
	list->insertLeft(n);
}

int ADTList::size() {
	return list->size();
}

bool ADTList::isLast(Node* n) {
	return list->isLast(n);
}

bool ADTList::isFirst(Node* n) {
	return list->isFirst(n);
}
