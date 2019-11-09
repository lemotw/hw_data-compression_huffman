#include "filebitreader.h"
#include <stdio.h>

void initFileBitReader(FileBitReader *fr)
{
    fr->fp = NULL;
    fr->current_data = 0;
    fr->remain_bit = 0;
}

int getFileBit(FileBitReader *fr, unsigned char* data)
{
    if(fr->remain_bit == 0)
    {
        if((fr->current_data = getc(fr->fp)) == EOF)
            return 0;
        fr->remain_bit = 8;
    }

    *data = ((0x80 >> (8-fr->remain_bit)) & fr->current_data) >> (fr->remain_bit-1);
    fr->remain_bit--;
    return 1;
}

int getFileChar(FileBitReader *fr, unsigned char* data)
{
    if(fr->remain_bit == 0)
    {
        if((fr->current_data = getc(fr->fp)) == EOF)
            return 0;
        *data = fr->current_data;

        if((fr->current_data = getc(fr->fp)) == EOF)
            return 0;
        fr->remain_bit = 8;
        return 1;
    }

    if(fr->remain_bit == 8)
    {
        *data = fr->current_data;
        if((fr->current_data = getc(fr->fp)) == EOF)
            return 0;
        return 1;
    }

    *data = (((short)fr->current_data << 8) & (0xff00 >> 8-fr->remain_bit)) >> fr->remain_bit;
    //ex 01001010, remain_bit 4 
    //data set as 1010xxxx, xxxx set to next char data.

    if((fr->current_data = getc(fr->fp)) == EOF)
        return 0;
    *data |= ((fr->current_data << 8-fr->remain_bit) & 0xff00) >> 8;
    //append remain bit behind data.

    return 1;
}