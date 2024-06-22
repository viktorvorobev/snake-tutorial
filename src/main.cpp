#include <iostream>
#include <deque>
#include <raylib.h>
#include <raymath.h>

#define SCREEN_WIDTH 750  // px
#define SCREEN_HEIGHT 750 // px
#define CELL_SIZE 30      // px

Color green{173, 204, 96, 255};
Color darkGreen{43, 51, 24, 255};

double lastUpdateTime{0};

bool ElementInDeque(Vector2 &element, std::deque<Vector2> &deque)
{
    for (unsigned int i = 0; i < deque.size(); i++)
    {
        if (Vector2Equals(deque[i], element))
        {
            return true;
        }
    }
    return false;
}

bool eventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

class Snake
{
public:
    std::deque<Vector2> body{Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction{1, 0};

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
    void Update()
    {
        body.pop_back();
        body.push_front(Vector2Add(body[0], direction));
    }
};

class Food
{
public:
    Vector2 position;
    Texture2D texture;

    Food(std::deque<Vector2> &snakeBody)
    {
        Image image = LoadImage("../graphics/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);

        position = GenerateRandomPos(snakeBody);
    }

    void Draw()
    {
        DrawTexture(texture, position.x * CELL_SIZE, position.y * CELL_SIZE, WHITE);
    }

    Vector2 GenerateRandomPos(std::deque<Vector2> &snakeBody)
    {
        Vector2 newPosition;
        do
        {
            float x = GetRandomValue(0, SCREEN_WIDTH / CELL_SIZE - 1);
            float y = GetRandomValue(0, SCREEN_HEIGHT / CELL_SIZE - 1);
            newPosition = Vector2{x, y};
        } while (ElementInDeque(newPosition, snakeBody));
        return newPosition;
    }

private:
    int cellPart = CELL_SIZE / 3;
};

class Game
{
public:
    Snake snake{};
    Food food{snake.body};

    void Draw()
    {
        food.Draw();
        snake.Draw();
    }

    void Update()
    {
        snake.Update();
        CheckCollisionWithFood();
    }

    void CheckCollisionWithFood()
    {
        if (Vector2Equals(snake.body[0], food.position))
        {
            food.position = food.GenerateRandomPos(snake.body);
        }
    }
};

int main()
{
    std::cout << "Starting the game..." << std::endl;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Retro Snake game");
    SetTargetFPS(60); // limit FPS

    Game game{};

    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        if (eventTriggered(0.2))
        {
            game.Update();
        }

        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1)
        {
            game.snake.direction = {0, -1};
        }
        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1)
        {
            game.snake.direction = {0, 1};
        }
        if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1)
        {
            game.snake.direction = {-1, 0};
        }
        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1)
        {
            game.snake.direction = {1, 0};
        }

        ClearBackground(green); // clear the screen and fill the background

        game.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
