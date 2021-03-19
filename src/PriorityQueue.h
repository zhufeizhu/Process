#pragma once

class Node;
class ListItem;

class PriorityQueue{
private:
    Node *front;
    Node *back;
    int size;
public:
    PriorityQueue();
    int getSize();
    bool isEmpty();
    void enqueue(ListItem *item);
    ListItem *getFront();
    ListItem *dequeue();
};