#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "bitwise.h"

//Tree right 1, left 0.
typedef struct Node {
	unsigned char show;
	char data;

	void* parent;
	void* right;
	void* left;

	unsigned char status;
	// 1->NYT 0->Leave 2->Node
} Node;

Node* newNode();
Node* findNode(Node* root, char data);
void getNodeBits(Node* root, BitWiseStack* s);
Node* fixed(Node* root, unsigned char data);

void updateShows(Node* root);

Node* findSameWeightNode(Node* root);

void updateHuffmanTree(Node* root);
void huffmanCoding(Node* root, char data, BitWiseStack* s);

#endif