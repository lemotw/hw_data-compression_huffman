#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "bitwise.h"

BitWise* newBitWise(unsigned char val, unsigned char bit)
{
    BitWise* rt = (BitWise*)malloc(sizeof(BitWise));
    rt->val = val;
    rt->bit = bit;
    rt->parent = NULL;
    rt->next = NULL;
    return rt;
}

void push_back_Bit(BitWiseStack* s, unsigned char val)
{
    if(isBitWiseEmpty(s))
    {
        val = val & 0x1;
        //Get only last one bit.
        s->front = newBitWise(val, 1);
        s->back = s->front;
        return;
    }

    if(s->back->bit == 8)
    {
        val = val & 0x1;
        //Get only last one bit.
        BitWise* new = newBitWise(val, 1);
        new->parent = s->back;
        s->back->next = new;
        s->back = new;
        return;
    }

    s->back->val = (s->back->val << 1) | (val & 0x1);
    //Shift left and append val last one bit to s->back->val.
    s->back->bit++;

    if(s->back->bit > 8)
    {
        printf("\n%p\n", s->back);
        printf("bits:%d val: %d", s->back->bit, s->back->val);
    }
}

void push_back_Char(BitWiseStack* s, unsigned char val)
{
    if(isBitWiseEmpty(s))
    {
        s->front = newBitWise(val, 8);
        s->back = s->front;
        return;
    }

    if(s->back->bit == 8)
    {
        BitWise* new = newBitWise(val, 8);
        new->parent = s->back;
        s->back->next = new;
        s->back = new;
        return;
    }

    int a =0;

    //Need two node to carry 8bits.
    unsigned char nbit = 8 - s->back->bit;
    if(s->back->bit > 8)
        a = a+2;
    s->back->val = (s->back->val << nbit) | ((((short)val << nbit) & 0xff00) >> 8);
    s->back->bit = 8;

    //Remain last un set bit.
    val &= (0x00ff >> nbit);

    //New and set bitwise.
    BitWise* new = newBitWise(val , 8-nbit);
    new->parent = s->back;
    s->back->next = new;
    s->back = new;
}

unsigned char pop_back_Bit(BitWiseStack* s)
{
    if(isBitWiseEmpty(s))
        return 2;
    
    if(s->back->bit <= 0)
    {
        BitWise* delete = s->back;
        s->back = s->back->parent;
        s->back->next = NULL;
        free(delete);
        return pop_back_Bit(s);
    }

    //Pop out last one bit.
    unsigned char rt = s->back->val & 0x1;
    s->back->val = s->back->val >> 1;
    s->back->bit--;
    return rt;
}

int pop_front_Char(BitWiseStack* s, unsigned char data)
{
    if(isBitWiseEmpty(s))
        return 0;
    data = s->front->val;

    if(s->front == s->back)
    {
        s->front = NULL;
        s->back = s->front;
        return 1;
    }
    BitWise* temp = s->front;
    s->front = temp->next;
    free(temp);

    return 1;
}

int isBitWiseEmpty(BitWiseStack* s)
{
    return (s->front == s->back) && (s->front == NULL || s->front->bit == 0);
}

void killBitWiseStack(BitWiseStack* s, BitWiseStack* ss)
{
    BitWise* temp = s->front;
    while(temp != NULL)
    {
        s->front = s->front->next;
        free(temp);
        temp = s->front;
    }
}

void printBitWise(BitWiseStack* s)
{
    BitWise* get = s->front;
    while(get != NULL)
    {
        unsigned char data = get->val;

        if(get->bit < 8)
            data = data << (8 - get->bit);

        for(int i=0; i<8 ;++i)
        {
            printf("%d", (data & 0x80) >> 7);
            data <<= 1;

            if(get->bit < 8)
                if(get->bit == i+1)
                    printf(",");
        }

        printf(" | ");
        get = (BitWise*)get->next;
    }

    printf("\n");
}

void outputFile(BitWiseStack* s, FILE* out)
{
    unsigned char data;
    BitWise* get = s->front;

    while(get != NULL)
    {
        data = get->val;
        if(get->bit < 8)
            data = data << (8 - get->bit);

        putc(data, out);
        get = (BitWise*)get->next;
    }
}