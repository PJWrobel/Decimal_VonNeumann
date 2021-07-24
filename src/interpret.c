#include<stdio.h>
#include<stdlib.h>

#include "comp.h"

const char *KEYWORDS[7] = {"END","ADD","INV","COPY","GOTO","IFGRT","IFEQ"};

int interpretProgram(char *filename)
{
    struct machine vm;

    char lineBuffer[20];
    char *labels[50]; //max 50 labels
    card labelsIndex[50];
    
    File *fp = fopen("programs/main.txt","r");
    int programSize;
    int labelsSize = 0;
    for(programSize = 0; *fp != EOF; fp++, programSize++)
    {
        strcpy(vm.label[i],*fp);
    }
    fclose(fp);

    for(int i=0; i < programSize; i++)
    {   
        char *line = vm.label[i];
        if(*line == '*')
        {
            line++;
            for(int label=0; label < labelsSize; label++)
            {
                if(strcmp(line, labels[label]) == 0)
                {
                    vm.ram[i] = labelsIndex[label];
                }
            }
        }
        for(int key = 0; key < 7; key++)
        {
            if(strcmp(KEYWORDS[key], line) == 0)
            {
                vm.ram[i] = key;
            }
        }
    }
    return 0;
}
