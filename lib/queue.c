#include <stddef.h>
#include <stdlib.h>
#include "queue.h"
#include "huffman.h"

void push_Queue_Node(Queue* q, Node* val)
{
    QueueNode* new_node = (QueueNode*)malloc(sizeof(QueueNode));
    new_node->data = val;
    new_node->next = NULL;

    if(isQueueEmpty(q))
    {
        q->back = new_node;
        q->front= new_node;
        return;
    }

    q->back->next = new_node;
    q->back = new_node;
}

Node* pop_Queue_Node(Queue* q)
{
    if(isQueueEmpty(q))
        return NULL;
    else if(q->back == q->front)
    {
        Node* rt = q->front->data;
        free(q->front);
        q->back = NULL;
        q->front= NULL;
        return rt;
    }

    QueueNode* temp = (QueueNode*)q->front->next;
    Node* rt = q->front->data;
    free(q->front);
    q->front = temp;
    return rt;
}

int isQueueEmpty(Queue* q)
{
    return ((q->front == NULL) && (q->front == q->back));
}

void killQueue(Queue* q)
{
    QueueNode* temp;
    while(q->front != NULL)
    {
        temp = q->front;
        q->front = (QueueNode*)q->front->next;
        free(temp);
    }
}