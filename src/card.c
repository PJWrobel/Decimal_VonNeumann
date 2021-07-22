#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

#define card uint16_t
#define ASCII_OFFSET 48 //ascii '0' = 48
#define MAX_CARD 999

card overflow(card c)
{   if( c > MAX_CARD)
        return c - 1000;
    return c;
}

card addCards(card x, card y)
{   return overflow(x + y);
}

card inverse(card x)
{   return MAX_CARD - x;
}

card subCards(card x, card y)   //subtract cards: a - b := a + ~b + 1 
{   return overflow( x+inverse(y)+1 );
}

char* cardToStr(card c)
{   char *str = malloc(4);
    for(int i=0; i < 3; i++)
    {   
        str[2 - i] = c % 10 + ASCII_OFFSET;
        c /= 10;
    }
    str[3] = '\0';
    return str;
}

void printCard(card c)
{   printf("%s\n", cardToStr(c));
}
