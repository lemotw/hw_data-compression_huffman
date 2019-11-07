#ifndef QUEUE_NODE
#define QUEUE_NODE

#include "huffman.h"

typedef struct QueueNode {
    void* next;
    Node* data;
} QueueNode;

typedef struct Queue {
	QueueNode* back;
	QueueNode* front;
} Queue;

void push_Queue_Node(Queue* q, Node* val);
Node* pop_Queue_Node(Queue* q);
//Need pop if you don't need Node*
int isQueueEmpty(Queue* q);
void killQueue(Queue* q);

#endif