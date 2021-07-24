#ifndef CARD_H_
#define CARD_H_


#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

#define card uint16_t
#define ASCII_OFFSET 48 //ascii '0' = 48
#define MAX_CARD 999

card overflow(card c);
card addCards(card x, card y);
card inverse(card x);
card subCards(card x, card y);
char* cardToStr(card c);
void printCard(card c);

#endif
