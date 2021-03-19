#include "PriorityQueue.h"
#include "ListItem.h"
#include "Node.h"

PriorityQueue::PriorityQueue():front(nullptr),back(nullptr),size(0){};

bool PriorityQueue::isEmpty(){ 
	return size == 0; 
}

void PriorityQueue::enqueue(ListItem *item){
	// special case: adding to empty queue
	if(front == nullptr){
		front = new Node(item, nullptr);
		back = front;
	} else {
        if (item->compareTo(front->getItem()) > 0){
            //表明待插入的节点应该为首节点
            Node *node = new Node(item,front);
            front = node;
        } else{
            Node *pre = front;
            Node *next = front->getNext();
            while(next && item->compareTo(next->getItem()) < 0){
                //next节点存在且优先级低于next节点时 向后遍历
                pre = next;
                next = next->getNext();
            }
            //当跳出循环时表明当前节点一定比pre节点优先级低 且next节点不存在或者比其优先级高
            Node *node = new Node(item,next);
            pre->setNext(node);
            if (!next){
                //表明需要更新back指针
                back = node;
            }
        }
	}
	size++;
}// enqueue

ListItem *PriorityQueue::dequeue(){
	ListItem *theItem = nullptr;
	Node *theNode = front;
	if(front != nullptr){
		theItem = front->getItem();
		// special case: removing last item
		if(front == back){
			front = back = nullptr;
		} else {
			front = front->getNext();
		}
		size--;
		delete(theNode);
	}
	return theItem;
}// dequeue


ListItem *PriorityQueue::getFront(){
	ListItem *theItem = nullptr;
	if(front != nullptr){
		theItem = front->getItem();
	}
	return theItem;
}// getFront
