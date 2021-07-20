#include<stdio.h>
#include<stdint.h>

#define card unit64_t
#define ASCII_OFFSET 48 //ascii '0' == 48

char* cardToStr(card c)
{
    char *digit = (* char) &c;
    for(int i=0; i<3; i++)
    {
        *digit = *(digit+1) + ASCII_OFFSET;
        digit++;
    }
    *digit = '\0';
    return digit-3;
}

void printCard(card c){ printf("%s\n", cardToStr(c)) }

card addCards(card a, card b)
{   card ret;
    return ret;
}
card subCards(){}



int main()
{   
}
