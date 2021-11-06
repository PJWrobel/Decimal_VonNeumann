#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "raylib.h"

#include "comp.h"

#define SW 1366
#define SH 768

#define OFFWHITE    (Color){222,200,140,255}
#define PASTEL_RED    (Color){255,50 ,50 ,255}
#define PASTEL_BLUE   (Color){51 ,95 ,255,255}
#define PASTEL_YELLOW (Color){255,230,50 ,255}
#define PASTEL_GREEN (Color){50,120,0,255}

#define END 0
#define ADD 1
#define INV 2
#define COPY 3
#define GOTO 4
#define IFGRT 5
#define IFEQ 6

void drawCard(card c, int x, int y, Color color, _Bool big, card index, char *label);
void drawMachine(struct machine vm, int ramSize);

//--------bezi curve--------
typedef struct point{
    double x,y;
}point;

struct beziCurve_4{
    point *p;
};
void DrawCurve4(struct beziCurve_4 c);
point get_midpoint(point p1, point p2, double i);
//-------------------------


int main(void)
{
    struct machine vm = {0, {4,9,33,241,0,0,1,0,1,3,3,5,6,2,8,37,1,3,5,7,5,7,5,28,1,4,6,4,3,7,5,1,8,6,8,4,12,0},{"GOTO","*COPY","x","y","r1","r2","#1","t","i","COPY","*y","*r2","IFEQ","*x","*i","*END","ADD","*y","*r2","*t","IFGRT","*t","*r2","*COPY","ADD","*r1","*1","*r1","COPY","*t","*r2","ADD","*i","*1","*i","GOTO","*IFEQ","END"}};
    
    InitWindow(SW, SH, "TEMPLATE");
    
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
    	//if (IsKeyPressed(KEY_ENTER))
        //{
		    tick(&vm);    
        //}
        if (IsKeyPressed(KEY_RIGHT))
        {
            vm.pc++;
        }
        if (IsKeyPressed(KEY_LEFT))
        {
            vm.pc--;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            vm.ram[vm.pc]--; //underflow not detected
        }
        if (IsKeyDown(KEY_UP))
        {
            vm.ram[vm.pc]++; //same with overflow
        }

        BeginDrawing();
        drawMachine(vm,100);
        ClearBackground((Color){13,13,20,255});
        EndDrawing();
    }
    CloseWindow();        // Close window and OpenGL context
    return 0;
}

void drawCard(card c, int x, int y, Color color, _Bool big, card index, char *label)
{
    char *cardstr = cardToStr(c, true);
    int rectLineWidth = 3;
    int digitOffset = 16;
    int fontSize = 20;
    int rectWidth = 14;
    int rectHeight = 18;
    int arugh = 2;

    if(big)
    {
        rectLineWidth=4;
        digitOffset = 31;
        fontSize = 40;
        rectWidth = 28;
        rectHeight = 36;
        arugh = 4;
        
    }

    for(int digit=0; digit<3; digit++)
    {
        for(int i=1; i<rectLineWidth; i++)
        {
            DrawRectangleLines((digit * digitOffset) + x - i, y - i, rectWidth + i*2, rectHeight + i*2, color);
        }
        DrawText(&cardstr[digit * 2], digit*digitOffset+x+arugh, y, fontSize, OFFWHITE);
    }
    DrawText(cardToStr(index, false),x,y+rectHeight+4,fontSize/2,OFFWHITE); //index
    DrawText(label,x,y-fontSize/2-2,fontSize/2,OFFWHITE); //label
}

void drawMachine(struct machine vm, int ramSize)
{   
    drawCard(vm.pc, 150, 100, PASTEL_RED, true, 5000, "program counter");
    drawCard(vm.ram[vm.pc], 400, 100, PASTEL_YELLOW, true, vm.pc, "instruction");
    
    int i=0;
    
    for(int row=0; row<13; row++)
    {
        for(int col=0; col<8 && i<ramSize; col++, i++)
        {
            drawCard(vm.ram[i], 850 + col*60, 100 + row*50, PASTEL_GREEN, false, i, vm.label[i]);
        }
    }

    int instructionSize = 1;
    card index = vm.pc;
    switch(vm.ram[index])
    {   
        case ADD:
            drawCard(vm.ram[vm.ram[index+1]], 300, 300, PASTEL_BLUE, true, 5000, " ");//a
            drawCard(vm.ram[vm.ram[index+2]], 300, 350, PASTEL_BLUE, true, 5000, " ");//b
            DrawRectangle(290,395,100,4,OFFWHITE);
            drawCard(addCards(vm.ram[vm.ram[index+1]], vm.ram[vm.ram[index+2]]), 300, 410, PASTEL_BLUE, true, 5000, " ");//out
    }

    switch(vm.ram[index])
    {
        case END:
            instructionSize = 1;
            break;
        case GOTO:
            instructionSize = 2;
            break;
        case COPY:
        case INV:
            instructionSize = 3;
            break;
        case ADD:
        case IFGRT:
        case IFEQ:
            instructionSize = 4;
            break;
    }
    //------------instruction boxes-------------
    void drawRect(card index, Color color)
    {   
        int row = index / 8;
        int col = index % 8;
        
        DrawRectangleLines(843 + col*60,86+row*50,60,48,color);
        DrawRectangleLines(842 + col*60,85+row*50,62,50,color);
    }
    for(i=1; i<instructionSize; i++)
    {   drawRect(index + i, GRAY);
    }
    drawRect(index, PASTEL_YELLOW);
}

void DrawCurve4(struct beziCurve_4 c)
{
    point intrm[5], final;
    point temp = {0.0,0.0};
    for(double i=0.0; i < 101; i+=1.0)
    {
        intrm[0] = get_midpoint(c.p[0],c.p[1],i);
        intrm[1] = get_midpoint(c.p[1],c.p[2],i);
        intrm[2] = get_midpoint(c.p[2],c.p[3],i);
        intrm[3] = get_midpoint(intrm[0],intrm[1],i);
        intrm[4] = get_midpoint(intrm[1],intrm[2],i);
        final = get_midpoint(intrm[3],intrm[4],i);
        if(temp.x == 0)
        {
            temp = final;
        }
        DrawLine(final.x, final.y, temp.x, temp.y, RED);
        temp = final;
    }
}
point get_midpoint(point p1, point p2, double i)
{
    point ret_p = {0.0,0.0};
    ret_p.x = (p2.x - p1.x) * (i/100.0) + p1.x;
    ret_p.y = (p2.y - p1.y) * (i/100.0) + p1.y;
    return ret_p;
 }

