#include <stdio.h>
#include "huffman.h"
#include "filebitreader.h"

int main(int argc, char* argv[])
{
    FileBitReader fr;
    initFileBitReader(&fr);
    FILE* fp = fopen(argv[1], "r");
    FILE* fo = fopen("decode_result", "w");
    fr.fp = fp;

	Node* root = newNode();
    Node* temp = root;
    Node* sameWei;
    Node* tempData;

    if(fp == NULL || fo == NULL)
	{
		printf("File open failure!!!");
		return 1;
	}

    unsigned int count = 0;
    count |= (unsigned int)getc(fp) << 24;
    count |= (unsigned int)getc(fp) << 16;
    count |= (unsigned int)getc(fp) << 8;
    count |= (unsigned int)getc(fp);
    unsigned char data;
    while(count != 0)
    {
        if(temp->status == 1)
        {
            if(getFileChar(&fr, &data) == 0)
                break;
            updateHuffmanTree(fixed(temp, data));
            putc(data, fo);
            temp = root;
            count--;
            continue;
        }

        if(temp->status == 0)
        {
            putc(temp->data, fo);
            count--;

            sameWei = findSameWeightNode(temp);
            if(sameWei != NULL)
            {
                if( ((Node*)sameWei->parent)->right == sameWei)
                    ((Node*)sameWei->parent)->right = temp;
                if( ((Node*)sameWei->parent)->left == sameWei)
                    ((Node*)sameWei->parent)->left = temp;

                //Set find's parent right or left link.
                if( ((Node*)temp->parent)->right == temp)
                    ((Node*)temp->parent)->right = sameWei;
                if( ((Node*)temp->parent)->left == temp)
                    ((Node*)temp->parent)->left = sameWei;

                //Swap find and sameWei parent
                tempData = sameWei->parent;
                sameWei->parent = temp->parent;
                temp->parent = tempData;
            }

            temp->show++;
            updateHuffmanTree(temp);
            temp = root;
            continue;
        }

        if(getFileBit(&fr, &data) == 0)
            break;
        
        if(data)
            temp = (Node*)temp->right;
        else
            temp = (Node*)temp->left;
    }

    return 0;
}
