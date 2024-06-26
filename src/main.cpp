#include <iostream>
#include <deque>
#include <raylib.h>
#include <raymath.h>

#define TITLE "Retro snake game"
#define SCREEN_WIDTH 750  // px
#define SCREEN_HEIGHT 750 // px
#define CELL_SIZE 30      // px
#define OFFSET 75         // px, borders around the screen

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
private:
    std::deque<Vector2> INITIAL_BODY{Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};

public:
    Vector2 DirectionRight{1, 0};
    Vector2 DirectionLeft{-1, 0};
    Vector2 DirectionUp{0, -1};
    Vector2 DirectionDown{0, 1};

    std::deque<Vector2> body = INITIAL_BODY;
    Vector2 direction = DirectionRight;
    bool addSegment = false;

    void Draw()
    {
        for (unsigned int i = 0; i < body.size(); i++)
        {
            float x = (body[i].x * CELL_SIZE) + OFFSET;
            float y = (body[i].y * CELL_SIZE) + OFFSET;

            Rectangle segment{x, y, CELL_SIZE, CELL_SIZE};
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        }
    }
    void Update()
    {
        body.push_front(Vector2Add(body[0], direction));
        if (addSegment)
        {
            addSegment = false;
        }
        else
        {
            body.pop_back();
        }
    }

    void Reset()
    {
        body = INITIAL_BODY;
        direction = DirectionRight;
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
        DrawTexture(texture, (position.x * CELL_SIZE) + OFFSET, (position.y * CELL_SIZE) + OFFSET, WHITE);
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
    bool running = true;
    int score = 0;

    void Draw()
    {
        food.Draw();
        snake.Draw();
    }

    void Update()
    {
        if (!running)
        {
            return;
        }
        snake.Update();
        CheckCollisionWithFood();
        CheckCollisionWithEdges();
        CheckCollisionWithTail();
    }

    void CheckCollisionWithFood()
    {
        if (Vector2Equals(snake.body[0], food.position))
        {
            food.position = food.GenerateRandomPos(snake.body);
            snake.addSegment = true;
            score++;
        }
    }

    void CheckCollisionWithEdges()
    {
        if (snake.body[0].x == SCREEN_WIDTH / CELL_SIZE || snake.body[0].x == -1)
        {
            GameOver();
        }
        else if (snake.body[0].y == SCREEN_HEIGHT / CELL_SIZE || snake.body[0].y == -1)
        {
            GameOver();
        }
    }

    void CheckCollisionWithTail()
    {
        std::deque<Vector2> headlessBody = snake.body;
        headlessBody.pop_front();
        if (ElementInDeque(snake.body[0], headlessBody))
        {
            GameOver();
        }
    }

    void GameOver()
    {
        snake.Reset();
        food.position = food.GenerateRandomPos(snake.body);
        running = false;
        score = 0;
    }
};

int main()
{
    InitWindow(SCREEN_WIDTH + 2 * OFFSET, SCREEN_HEIGHT + 2 * OFFSET, TITLE);
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
            game.snake.direction = game.snake.DirectionUp;
            game.running = true;
        }
        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1)
        {
            game.snake.direction = game.snake.DirectionDown;
            game.running = true;
        }
        if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1)
        {
            game.snake.direction = game.snake.DirectionLeft;
            game.running = true;
        }
        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1)
        {
            game.snake.direction = game.snake.DirectionRight;
            game.running = true;
        }

        ClearBackground(green); // clear the screen and fill the background

        Rectangle border{OFFSET - 5, OFFSET - 5, SCREEN_WIDTH + 10, SCREEN_HEIGHT + 10};
        DrawRectangleLinesEx(border, 5, darkGreen);
        DrawText(TITLE, OFFSET - 5, 20, 40, darkGreen);
        DrawText(TextFormat("Score: %i", game.score), OFFSET - 5, OFFSET + SCREEN_HEIGHT + 10, 40, darkGreen);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
