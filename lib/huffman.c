#include <stddef.h>
#include <stdlib.h>
#include "huffman.h"
#include "bitwise.h"
#include "queue.h"

Node* newNode()
{
	Node* node;
	node = (Node*)malloc(sizeof(Node));
	node->show = 0;
	node->data = 0;

	node->parent = NULL;
	node->right = NULL;
	node->left = NULL;

	node->status = 1;
	return node;
}

Node* findNode(Node* root, char data)
{
    Queue q; Node* per; Node* NYT;
    q.back = NULL; q.front = NULL;
    push_Queue_Node(&q, root);
    
    //level order 
    while(!isQueueEmpty(&q))
    {
        per = pop_Queue_Node(&q);

        if(!per->status && per->data == data)
        {
            killQueue(&q);
            return per;
        }
        if(per->status == 1)
            NYT = per;

        if(per->right != NULL)
            push_Queue_Node(&q, (Node*)per->right);
        if(per->left != NULL)
            push_Queue_Node(&q, (Node*)per->left);
    }

    killQueue(&q);
    return NYT;
}

void getNodeBits(Node* root, BitWiseStack* s)
{
    if(root->parent == NULL)
        return;

    BitWiseStack temp;
    temp.back = NULL; temp.front = NULL;
    //Check current root is parent's right or left leave.1
    //left->0  right->1
    while(root->parent != NULL)
    {
        if( ((Node*)root->parent)->left == root)
            push_back_Bit(&temp, 0);
        if( ((Node*)root->parent)->right == root)
            push_back_Bit(&temp, 1);

        root = (Node*)root->parent;
    }

    while(!isBitWiseEmpty(&temp))
        push_back_Bit(s, pop_back_Bit(&temp));

    killBitWiseStack(&temp, s);
}

Node* fixed(Node* root, unsigned char data)
{
    root->right = newNode();
    root->left = newNode();
    ((Node*)root->left)->parent = (void*)root;
    ((Node*)root->right)->parent = (void*)root;

    ((Node*)root->right)->status = 0;
    ((Node*)root->right)->data = data;
    ((Node*)root->right)->show++;

    root->status = 2;
    return (Node*)root->right;
}

Node* findSameWeightNode(Node* root)
{
    Node* pivot = (Node*)root->parent;
    Node* rt = NULL;

    while(pivot != NULL)
    {
        if( ((Node*)pivot->left)->show > root->show )
            break;

        if( ((Node*)pivot->right)->status == 0 && ((Node*)pivot->right)->show == root->show )
            rt = (Node*)pivot->right;

        if( ((Node*)pivot->left)->status == 0 && ((Node*)pivot->left)->show == root->show )
            rt = (Node*)pivot->left;

        pivot = (Node*)pivot->parent;
    }

    return rt;
}

void updateHuffmanTree(Node* root)
{
    while(root != NULL)
    {
        if((Node*)root->right != NULL && (Node*)root->left)
        {
            root->show = ((Node*)root->right)->show + ((Node*)root->left)->show;

            if( ((Node*)root->left)->show > ((Node*)root->right)->show )
            {
                Node* temp = (Node*)root->right;
                root->right = root->left;
                root->left = temp;
            }
        }

       root = (Node*)root->parent;
    }
}

void huffmanCoding(Node* root, char data, BitWiseStack* s)
{
    Node* find = findNode(root, data);
    Node* sameWei;Node* tempData;
    if(find->status == 1)
    {
        getNodeBits(find, s);
        updateHuffmanTree(fixed(find, data));
        push_back_Char(s, data);
    }

    if(!find->status)
    {
        getNodeBits(find, s);
        //Swap same weight node(Closest root one).
        sameWei = findSameWeightNode(find);
        if(sameWei != NULL)
        {
            //Set sameWei's parent right or left link.
            if( ((Node*)sameWei->parent)->right == sameWei)
                ((Node*)sameWei->parent)->right = find;
            if( ((Node*)sameWei->parent)->left == sameWei)
                ((Node*)sameWei->parent)->left = find;

            //Set find's parent right or left link.
            if( ((Node*)find->parent)->right == find)
                ((Node*)find->parent)->right = sameWei;
            if( ((Node*)find->parent)->left == find)
                ((Node*)find->parent)->left = sameWei;

            //Swap find and sameWei parent
            tempData = sameWei->parent;
            sameWei->parent = find->parent;
            find->parent = tempData;
        }

        find->show++;
        updateHuffmanTree(find);
    }
}