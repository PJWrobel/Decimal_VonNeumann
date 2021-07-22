#include<stdio.h>
#include"card.h"

#define CMD_REG 0
#define A_REG 1
#define B_REG 2
#define OUT_REG 3

struct machine
{   card ram[1000];
};

void init(struct machine *vm)
{   for(int i=0; i<1000; i++)
    {   vm->ram[i] = 0;
    }
}

void loadProgram(struct machine *vm, card *program, size_t pgrmSize)
{   for(int i=0; i<pgrmSize; i++){ //900 max size of program
        vm->ram[i + 10] = program[i];
    }
}

enum command { END, ADD, INV, COPY, GOTO, IFGRT, IFEQ };

int tick(struct machine *vm)
{
    card *ram = vm->ram;
    card *pc  = &ram[ CMD_REG ]; 
    card *a   = &ram[ A_REG ];
    card *b   = &ram[ B_REG ];
    card *out = &ram[ OUT_REG ];
    card cmd  = ram[ *pc ];
    
    if(cmd > 997){
        return -1;
    }
    
    switch(cmd)
    {   case END:
            return 0;
        case ADD:
            *out = addCards(*a,*b);
            break;
        case INV:
            *out = inverse(*a);
            break;
        case COPY:
            ram[ ram[ *pc+2 ]] = ram[ ram[ *pc+1 ]];
            *pc += 2;
            break;
        case GOTO:
            *pc = ram[ *pc+1 ];
            break;
        case IFGRT:
            if(*a > *b){
                *pc = ram[ *pc+1 ];
                return 1;
            }
            break;
        case IFEQ:
            if(*a == *b){
                *pc = ram[ *pc+1 ];
                return 1;
            }
            break;
    }
    //*pc++;error?
    vm->ram[CMD_REG]++;
    return 1;
}

void printRam(struct machine vm)
{   printf("[ %s : %s : %s : %s ] ", cardToStr(vm.ram[0]), cardToStr(vm.ram[1]), cardToStr(vm.ram[2]), cardToStr(vm.ram[3]));
    for(int i=100; i<120; i++)
    {   printf(" %s |", cardToStr(vm.ram[i]));
    }
}

int main()
{
    card program[] = {0,0,499,1,3,100,1,3,102,2,5,114,3,103,101,0};
    struct machine vm;
    loadProgram(&vm, program, 16);
    vm.ram[0] = 104;
    printRam(vm);

    return 0;
}
