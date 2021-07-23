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
        vm->ram[i + 100] = program[i];
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
