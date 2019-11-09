#include <stdio.h>
#include "huffman.h"
#include "bitwise.h"

int main(int argc, char* argv[])
{
	BitWiseStack s;
	s.back = NULL; s.front = NULL;
	Node* root = newNode();
	Node* temp;
	unsigned int count;

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
		count++;
	}
	putc((count&0xff000000) >> 24, outFP);
	putc((count&0x00ff0000) >> 16, outFP);
	putc((count&0x0000ff00) >> 8, outFP);
	putc(count&0x000000ff, outFP);
	outputFile(&s, outFP);

	fclose(readFP);
	fclose(outFP);
	return 0;
}