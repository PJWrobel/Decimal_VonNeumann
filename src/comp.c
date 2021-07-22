#include<stdio.h>
#include"card.h"

#define CMD_REG 0
#define A_REG 1
#define B_REG 2
#define OUT_REG 3

struct machine
{   card ram[1000];
};

enum command
{
    END, ADD, INV, COPY, GOTO, IFGRTR, IFEQ;
};

void __init__(struct machine vm)
{   
}

void tick(struct machine *vm)
{   card cmd = vm->ram[ vm->ram[ CMD_REG ] ];
    
}
int main()
{
    return 0;
}
