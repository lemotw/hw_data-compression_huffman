#ifndef FILE_BIT_READER
#define FILE_BIT_READER

#include <stdio.h>

typedef struct FileBitReader{
    FILE* fp;
    unsigned char current_data;
    unsigned char remain_bit;
}FileBitReader;

void initFileBitReader(FileBitReader *fr);
int getFileBit(FileBitReader *fr, unsigned char* data);
int getFileChar(FileBitReader *fr, unsigned char* data);

#endif