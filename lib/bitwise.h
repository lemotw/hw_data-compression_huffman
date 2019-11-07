#ifndef BITWISE_H
#define BITWISE_H

#include <stdio.h>

typedef struct BitWise {
    unsigned char val;
    unsigned char bit;
    void* parent;
    void* next;
} BitWise;

typedef struct BitWiseStack{
    BitWise* front;
    BitWise* back;
} BitWiseStack;


BitWise* newBitWise(unsigned char val, unsigned char bit);

void push_back_Bit(BitWiseStack* s, unsigned char val);
void push_back_Char(BitWiseStack* s, unsigned char val);

unsigned char pop_back_Bit(BitWiseStack* s);
unsigned char pop_front_Bit(BitWiseStack* s);

int isBitWiseEmpty(BitWiseStack* s);
void killBitWiseStack(BitWiseStack* s, BitWiseStack* ss);

void printBitWise(BitWiseStack* s);
void outputFile(BitWiseStack* s, FILE* out);

#endif