#include <iostream>
#include <raylib.h>

#define SCREEN_WIDTH 750  // px
#define SCREEN_HEIGHT 750 // px
#define CELL_SIZE 30      // px

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

class Food
{
public:
    Vector2 position = {5, 6}; // initial place for Food object

    void Draw()
    {
        for (int xOffset = 0; xOffset < 3; xOffset++)
        {
            for (int yOffset = 0; yOffset < 3; yOffset++)
            {
                if ((xOffset + yOffset) % 2)
                {
                    int xPos = (position.x * CELL_SIZE) + cellPart * xOffset;
                    int yPos = (position.y * CELL_SIZE) + cellPart * yOffset;
                    DrawRectangle(xPos, yPos, cellPart, cellPart, darkGreen);
                }
            }
        }
    }

private:
    int cellPart = CELL_SIZE / 3;
};

int main()
{
    std::cout << "Starting the game..." << std::endl;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Retro Snake game");
    SetTargetFPS(60); // limit FPS
    Food food = Food();

    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        ClearBackground(green); // clear the screen and fill the background

        food.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
