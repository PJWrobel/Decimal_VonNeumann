#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "raylib.h"

#include "comp.h"

#define SW 1366
#define SH 768

int main(void)
{
    card program[] =  {32,17,0,1,3,101,1,3,100,2,2,3,3,1,1,3,3,1,3,103,2,1,3,3,102};
            //{a,b,ret,1,copy,*b,*r1,copy,*a,*r2,inv,copy,*out,*r1,add,copy,*out,*a,copy,*1,*b,copy,*out,*ret};
            //(104){500,0,499,1,3,102,1,3,100,2,5,114,3,103,101,0};
    struct machine vm;
    init(&vm);
    loadProgram(&vm, program, 25);
    vm.ram[0] = 104;


    InitWindow(SW, SH, "TEMPLATE");
    //int framesCounter = 0;          // Useful to count frames
    SetTargetFPS(30);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
    	if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
        {
		//TODO:
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseWindow();        // Close window and OpenGL context
    return 0;
}
