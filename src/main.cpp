#include <iostream>
#include <raylib.h>

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int main()
{
    std::cout << "Starting the game..." << std::endl;

    InitWindow(750, 750, "Retro Snake game");
    SetTargetFPS(60); // limit FPS

    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        ClearBackground(green); // clear the screen and fill the background

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
