#include<stdio.h>
#include"card.h"

#ifndef COMP_H_
#define COMP_H_

#define CMD_REG 0
#define A_REG 1
#define B_REG 2
#define OUT_REG 3

struct machine{
    card pc;
    card ram[1000];
    char *label[1000];
};

void init(struct machine *vm);

void loadProgram(struct machine *vm, card *program, size_t pgrmSize);

enum command;

int tick(struct machine *vm);

void printRam(struct machine vm);

#endif
