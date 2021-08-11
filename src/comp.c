#include<stdio.h>
#include"card.h"

#define CMD_REG 0

#define END 0
#define ADD 1
#define INV 2
#define COPY 3
#define GOTO 4
#define IFGRT 5
#define IFEQ 6

struct machine
{   card pc;        //program counter
    card ram[1000];
    char *label[1000];
};

void init(struct machine *vm)
{   
    vm->pc = 0; //program counter register
    for(int i=0; i<1000; i++)
    {   
        vm->ram[i] = 0;
    }
}

void loadProgram(struct machine *vm, card *program, size_t pgrmSize)
{   
    for(int i=0; i<pgrmSize; i++)//900 max size of program
    {
        vm->ram[i] = program[i];
    }
}

int tick(struct machine *vm)
{
    card *ram = vm->ram;        //immutable
    card *cmd  = &ram[ vm->pc ]; 
    
    if(*cmd > 997)
    {   return -1;
    }
    
    switch(*cmd)
    {   case END:
            return 0;
        case ADD:
            ram[cmd[3]] = addCards(ram[cmd[1]], ram[cmd[2]]); // | ADD | *a | *b | *out | ..
            vm->pc += 4;
            break;
        case INV:
            ram[cmd[2]] = inverse(ram[cmd[1]]);
            vm->pc += 3;
            break;
        case COPY:
            ram[cmd[2]] = ram[cmd[1]];
            vm->pc += 3;
            break;
        case GOTO:
            vm->pc = cmd[1];
            break;
        case IFGRT:
            if(ram[cmd[1]] > ram[cmd[2]] ){
                vm->pc = cmd[3];
                return 1;
            }
            vm->pc += 4;
            break;
        case IFEQ:
            if(ram[cmd[1]] == ram[cmd[2]]){
                vm->pc = cmd[3];
                return 1;
            }
            vm->pc += 4;
            break;
    }
    return 1;
}

/*
void printRam(struct machine vm)
{   printf("[ %s : %s : %s : %s ]\n", cardToStr(vm.ram[0]), cardToStr(vm.ram[1]), cardToStr(vm.ram[2]), cardToStr(vm.ram[3]));
    for(int i=100; i<125; i++)
    {   printf("%s|", cardToStr(vm.ram[i]));
    }
    puts("");
}

int main()
{
    card program[] =  {32,17,0,1,3,101,1,3,100,2,2,3,3,1,1,3,3,1,3,103,2,1,3,3,102};
                //{a,b,ret,1,copy,*b,*r1,copy,*a,*r2,inv,copy,*out,*r1,add,copy,*out,*a,copy,*1,*b,copy,*out,*ret};
                //(104){500,0,499,1,3,102,1,3,100,2,5,114,3,103,101,0};
    struct machine vm;
    init(&vm);
    loadProgram(&vm, program, 25);
    vm.ram[0] = 104;

    do{
        printRam(vm);
        getchar();
    }while(tick(&vm));

    printRam(vm);

    return 0;
}
*/
