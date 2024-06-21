#include <iostream>
#include <raylib.h>

int main()
{
    std::cout << "Starting the game..." << std::endl;

    InitWindow(750, 750, "Retro Snake game");
    SetTargetFPS(60); // limit FPS

    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
