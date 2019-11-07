#include <stdio.h>
#include "huffman.h"
#include "bitwise.h"

int main(int argc, char* argv[])
{
	BitWiseStack s;
	s.back = NULL; s.front = NULL;
	Node* root = newNode();

	FILE* readFP = fopen(argv[1], "r");
	FILE* outFP = fopen("output", "w");


	if(readFP == NULL || outFP == NULL)
	{
		printf("File open failure!!!");
		return 1;
	}

	char ch;
	while((ch=getc(readFP)) != EOF)
	{
		huffmanCoding(root, ch, &s);
		if(s.back->bit > 8)
			break;
	}

	outputFile(&s, outFP);

	fclose(readFP);
	fclose(outFP);
	return 0;
}