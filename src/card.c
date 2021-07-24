#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<stdbool.h>

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

char* cardToStr(card c, _Bool separate) //{'9','\0','9','\0','9','\0'}
{   
    char *str = malloc(6);
    if(separate){
        str[1] = '\0';
        str[3] = '\0';
        str[5] = '\0';
        str[4] = c % 10 + ASCII_OFFSET;
        c /= 10;
        str[2] = c % 10 + ASCII_OFFSET;
        c /= 10; 
        str[0] = c % 10 + ASCII_OFFSET;
    } else {
        str[3] = '\0';
        str[2] = c % 10 + ASCII_OFFSET;
        c /= 10;
        str[1] = c % 10 + ASCII_OFFSET;
        c /= 10; 
        str[0] = c % 10 + ASCII_OFFSET;
    }
    return str;
}

void printCard(card c)
{   printf("%s\n", cardToStr(c, false));
}
