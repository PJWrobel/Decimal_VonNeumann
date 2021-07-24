#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "raylib.h"

#include "comp.h"

#define SW 1366
#define SH 768

void drawCard(card c, Font font, int x, int y, Color color)
{   DrawRectangleLines(x,y,x+10,y,color);
    DrawTextEx(font, cardToStr(c), (Vector2){x+2,y+1}, 20.0, 1.0, (Color){0,0,0,255});
}

int main(void)
{
    Font font = LoadFont("Enonymous_pro_bold.ttf");

    card program[] =  {32,17,0,1,3,101,1,3,100,2,2,3,3,1,1,3,3,1,3,103,2,1,3,3,102};
            //{a,b,ret,1,copy,*b,*r1,copy,*a,*r2,inv,copy,*out,*r1,add,copy,*out,*a,copy,*1,*b,copy,*out,*ret};
            //(104){500,0,499,1,3,102,1,3,100,2,5,114,3,103,101,0};
    struct machine vm;
    init(&vm);
    loadProgram(&vm, program, 25);
    vm.ram[0] = 999;


    InitWindow(SW, SH, "TEMPLATE");
    
    SetTargetFPS(30);

    while (!WindowShouldClose())
    {
    	if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
        {
		//TODO:
        }
        BeginDrawing();
        drawCard(vm.ram[0], font, 20, 20, RED);
        ClearBackground(GRAY);
        EndDrawing();
    }
    CloseWindow();        // Close window and OpenGL context
    return 0;
}
