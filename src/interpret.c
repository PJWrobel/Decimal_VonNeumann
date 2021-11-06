#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "comp.h"

char *keywords[7] = {"END","ADD","INV","COPY","GOTO","IFGRT","IFEQ"};

int strcmpAndLine(char *str1, char *str2)
{
    for(;*str1 && *str2; str1++, str2++)
        if(*str1 != *str2)
            return *str1 > *str2 ? 1 : -1;
    if(*str2 == ':')
        return 2;
    else return 0;
}

struct machine interpretProgram(char *filename)
{
    struct machine vm;

    char lineBuffer[20];
    char *labels[50]; //max 50 labels
    card labelsIndex[50];
    
    FILE *fp = fopen("programs/main.txt","r");
    int programSize;
    int labelsSize = 0;

    for(programSize = 0; fgets(lineBuffer, 20, fp) != NULL; fp++, programSize++) //copy from file to ram labels
    {
        strcpy(vm.label[programSize], lineBuffer);
    }
    fclose(fp);

    for(int i=0; i < programSize; i++) //iterate through program
    {   
        char *line = vm.label[i];
        switch(*line)
        { 
            case '*': //if pointer
                line++;
                for(int label=0; label < labelsSize; label++)
                {
                    if(strcmp(line, labels[label]) == 0) //if label found
                    {
                        vm.ram[i] = labelsIndex[label];
                    }
                }
                break;

            case '#': //constant num syntax
            
                vm.ram[i] = (card)atoi(line+1);
                labels[labelsSize++] = line; //strcpy?
                break;

            case 'A' ... 'Z': //uppercase
                for(int key = 0; key < 7; key++)
                {
                    if(strcmpAndLine(keywords[key], line) == 0)
                    {
                        vm.ram[i] = key;
                    }
                }
                break;

            case 'a' ... 'z'
                labels[labelsSize++] = line;
        }
    }
    return vm;
}
int main()
{
    struct machine vm = interpretProgram("programs/add6dig.pgm");
    return 0;
}
