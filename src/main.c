#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "raylib.h"

#include "comp.h"

#define SW 1366
#define SH 768
#define OFFWHITE (Color){222,200,140,255}



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
    //card program[] =  {4,0,0,0,32,17,0,1,3,5,1,3,4,2,2,3,3,1,1,3,3,1,3,7,2,1,3,3,6};
            //(104){500,0,499,1,3,102,1,3,100,2,5,114,3,103,101,0};
    
    struct machine vm = {
                {8,0,0,0,32,17,0,1,3,5,1,3,4,2,2,3,3,1,1,3,3,1,3,7,2,1,3,3,6},
                {"counter","a","b","out","x","y","ret","1","copy","*b","*r1","copy","*a","*r2","inv","copy","*out","*r1","add","copy","*out","*a","copy","*1","*b","copy","*out","*ret"} };
    //init(&vm);
    //loadProgram(&vm, program, 29);

    InitWindow(SW, SH, "TEMPLATE");
    
    SetTargetFPS(30);

    while (!WindowShouldClose())
    {

    	if (IsKeyPressed(KEY_ENTER))
        {
		    tick(&vm);    
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
    //-------draw ram--------

    drawCard(vm.ram[0], 150,100,(Color){255,50,50,255}, true, 0, vm.label[0]);
    drawCard(vm.ram[1], 150,300,(Color){51,95,255,255}, true, 1, vm.label[1]);
    drawCard(vm.ram[2], 500,300,(Color){51,95,255,255}, true, 2, vm.label[2]);
    drawCard(vm.ram[3], 325,600,(Color){51,95,255,255}, true, 3, vm.label[3]);
    drawCard(vm.ram[vm.ram[0]], 500,100,(Color){255,230,50,255}, true, vm.ram[0], vm.label[vm.ram[0]]);
    
    int i=4;
    
    drawCard(vm.ram[0], 850,50,(Color){255,50,50,255}, false, 0, vm.label[0]);
    drawCard(vm.ram[1], 910,50,(Color){51,95,255,255}, false, 1, vm.label[1]);
    drawCard(vm.ram[2], 970,50,(Color){51,95,255,255}, false, 2, vm.label[2]);
    drawCard(vm.ram[3], 1030,50,(Color){51,95,255,255}, false, 3, vm.label[3]);
   
    for(int row=0; row<13; row++)
    {
        for(int col=0; col<8 && i<ramSize; col++, i++)
        {
            drawCard(vm.ram[i], 850 + col*60, 100 + row*50, (Color){50,120,0,255}, false, i, vm.label[i]);
        }
    }
    //-----------bezi curve---------------
    point p1[4] = {{195,345},{195,400},{360,520},{360,580}};
    point p2[4] = {{196,345},{196,400},{361,520},{361,580}};
    point p3[4] = {{545,345},{545,400},{380,520},{380,580}};
    point p4[4] = {{546,345},{546,400},{381,520},{381,580}};

    struct beziCurve_4 bc1 = {p1};
    struct beziCurve_4 bc2 = {p2};
    struct beziCurve_4 bc3 = {p3};
    struct beziCurve_4 bc4 = {p4};

    DrawCurve4(bc1);
    DrawCurve4(bc2);
    DrawCurve4(bc3);
    DrawCurve4(bc4);

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

