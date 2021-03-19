#pragma once

class Node;
class ListItem;

class Queue {
private:
	Node *front;
	Node *back;
	int size;
public:
	Queue();
	int getSize();
	bool isEmpty();
	void enqueue(ListItem *item);
	ListItem *getFront();
	ListItem *dequeue();
}; // class Queue
