#ifndef _NODE_H
#define _NODE_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

class Node {
	public:
		//accepts the value to store at this node	
		Node(int v);
		//accepts the value to store at this node and change which nodes are the 
		//left and right of this node
		Node(int v,Node *p,Node *n);
		//changes which Node is the right of this one
		void setRight(Node* n);
		//changes which Node is to the left of this one
		void setLeft(Node* p);
		//
		Node* right();
		Node* left();
		int element();
		void setElement(int v);

	protected:
		int value;
		Node *next,*prev;
};

#endif 
