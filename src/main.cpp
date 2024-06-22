#include <iostream>
#include <deque>
#include <raylib.h>

#define SCREEN_WIDTH 750  // px
#define SCREEN_HEIGHT 750 // px
#define CELL_SIZE 30      // px

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

class Snake
{
public:
    std::deque<Vector2> body{Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};

    void Draw()
    {
        for (unsigned int i = 0; i < body.size(); i++)
        {
            float x = body[i].x * CELL_SIZE;
            float y = body[i].y * CELL_SIZE;

            Rectangle segment{x, y, CELL_SIZE, CELL_SIZE};
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        }
    }
};

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

    Food food{};
    Snake snake{};

    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        ClearBackground(green); // clear the screen and fill the background

        food.Draw();
        snake.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
