#include <stdio.h>
#include "huffman.h"
#include "bitwise.h"

int main()
{
	BitWiseStack s;
	s.front = NULL; s.back = NULL;
	Node* temp;
	char data_arr[] = {'A', 'B', 'C', 'D', 'D', 'B', 'A', 'E', 'C'};

	Node* root = newNode();

	for(int i=0; i<9 ;++i)
	{
		huffmanCoding(root, data_arr[i], &s);
		printBitWise(&s);
	}

	int a = 2;
	a = a++;
	
	return 0;
}
