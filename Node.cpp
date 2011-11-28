#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include "Node.h"

Node::Node(int v) 
{
	if(v >= 0 && v < 9999)
		value = v;
	else 
		value = (abs(v))%10000;
}

Node::Node(int v,Node *p,Node *n) : value(v), next(n), prev(p) {}

void Node::setRight(Node* n) 
{
	next = n;
}

void Node::setLeft(Node* p) 
{
	prev = p;
}

Node* Node::right() 
{
	return next;
}

Node* Node::left() 
{
	return prev;
}

int Node::element() 
{
	return value;
}

void Node::setElement(int v) 
{
	if(v >= 0 && v < 9999)
		value = v;
	else 
		value = (abs(v))%10000;
}
