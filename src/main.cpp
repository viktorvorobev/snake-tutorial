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
    Vector2 position;
    Texture2D texture;

    Food()
    {
        Image image = LoadImage("../graphics/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);

        position = GenerateRandomPos();
    }

    ~Food()
    {
        UnloadTexture(texture);
    }

    void Draw()
    {
        DrawTexture(texture, position.x * CELL_SIZE, position.y * CELL_SIZE, WHITE);
    }

    Vector2 GenerateRandomPos()
    {
        float x = GetRandomValue(0, SCREEN_WIDTH / CELL_SIZE - 1);
        float y = GetRandomValue(0, SCREEN_HEIGHT / CELL_SIZE - 1);
        return Vector2{x, y};
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
