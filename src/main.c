#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "raylib.h"

#include "comp.h"

#define SW 1366
#define SH 768
#define OFFWHITE (Color){222,200,140,255}

void drawCard(card c, int x, int y, Color color, _Bool big, card index, char *label){

    char *cardstr = cardToStr(c, true);
    int rectLineWidth = 3;
    int digitOffset = 16;
    int fontSize = 20;
    int rectWidth = 14;
    int rectHeight = 18;
    int arugh = 2;

    if(big){
        rectLineWidth=4;
        digitOffset = 31;
        fontSize = 40;
        rectWidth = 28;
        rectHeight = 36;
        arugh = 4;
        
    } else {
    }

    for(int digit=0; digit<3; digit++){
        for(int i=1; i<rectLineWidth; i++){
            DrawRectangleLines((digit * digitOffset) + x - i, y - i, rectWidth + i*2, rectHeight + i*2, color);
        }
        DrawText(&cardstr[digit * 2], digit*digitOffset+x+arugh, y, fontSize, OFFWHITE);
    }
    DrawText(cardToStr(index, false),x,y+rectHeight+4,fontSize/2,OFFWHITE); //index
    DrawText(label,x,y-fontSize/2-2,fontSize/2,OFFWHITE); //label
}

void drawMachine(struct machine vm, int ramSize)
{   
    //-------draw ram--------

    drawCard(vm.ram[0], 100,50,(Color){255,50,50,255}, true, 0, vm.label[0]);
    drawCard(vm.ram[1], 100,200,(Color){51,95,255,255}, true, 1, vm.label[1]);
    drawCard(vm.ram[2], 400,200,(Color){51,95,255,255}, true, 2, vm.label[2]);
    drawCard(vm.ram[3], 250,500,(Color){51,95,255,255}, true, 3, vm.label[3]);
    
    int i=4;
    
    drawCard(vm.ram[0], 850,50,(Color){255,50,50,255}, false, 0, vm.label[0]);
    drawCard(vm.ram[1], 910,50,(Color){51,95,255,255}, false, 1, vm.label[1]);
    drawCard(vm.ram[2], 970,50,(Color){51,95,255,255}, false, 2, vm.label[2]);
    drawCard(vm.ram[3], 1030,50,(Color){51,95,255,255}, false, 3, vm.label[3]);
   
    for(int row=0; row<13; row++){
        for(int col=0; col<8 && i<ramSize; col++, i++){
            drawCard(vm.ram[i], 850 + col*60, 100 + row*50, (Color){50,120,0,255}, false, i, vm.label[i]);
        }
    }
}


int main(void)
{
    card program[] =  {4,0,0,0,32,17,0,1,3,101,1,3,100,2,2,3,3,1,1,3,3,1,3,103,2,1,3,3,102};
            //{a,b,ret,1,copy,*b,*r1,copy,*a,*r2,inv,copy,*out,*r1,add,copy,*out,*a,copy,*1,*b,copy,*out,*ret};
            //(104){500,0,499,1,3,102,1,3,100,2,5,114,3,103,101,0};
    
    struct machine vm;
    init(&vm);
    loadProgram(&vm, program, 25);
    vm.ram[0] = 7;


    vm.label[0] = "counter";
    vm.label[1] = "a";
    vm.label[2] = "b";
    vm.label[3] = "out";


    InitWindow(SW, SH, "TEMPLATE");
    
    SetTargetFPS(30);

    while (!WindowShouldClose())
    {

    	if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
        {
		//TODO:
        }
        BeginDrawing();
        drawMachine(vm,100);
        ClearBackground((Color){13,13,20,255});
        EndDrawing();
    }
    CloseWindow();        // Close window and OpenGL context
    return 0;
}
