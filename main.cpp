#define RAYLIB_WIN_CONSOLE
#include "raylib.h"
#include "game.h"

#define snakeLength 100
#define  blockSize 40

const int screenWidth = 400;
const int screenHeight = 400;

int framescounter = 0;
Vector2 speed = {0,0};
int counterTail = 1;
bool run = true;
int GameSpeed = 8;

struct Snake_block
{
    Vector2 position;
    Color colour;
};

struct Food
{
    Vector2 position;
    Color colour;
    bool active;
};
    
Snake_block snake[snakeLength] = { 0 };
Food food = { 0 };
Vector2 snakePosition[snakeLength] = { 0 };

int main()
{
    InitWindow(screenWidth,screenHeight,"My Game");
    SetTargetFPS(60);

    InitGame();

    while (!WindowShouldClose() && run == true)
    {    
        UpdateGame();
    }

    CloseWindow();

    return 0;
}

void InitGame()
{
    snake[0].position = GetRandomPos();
    snake[0].colour = DARKBLUE;
    food.position = GetRandomPos();
    while (snake[0].position.x == food.position.x && snake[0].position.y == food.position.y)
    {
        food.position = GetRandomPos();
    }
    food.colour = RED;
    food.active = true;
}

void UpdateGame()
{
    Draw();
    Move();
}

void Move()
{
    Check_controls();
    for (int i = 0; i < counterTail; i++) snakePosition[i] = snake[i].position;
    if (framescounter%GameSpeed==0)
    {
        for (int i = 0; i < counterTail; i++)
        {
            if (i == 0)
            {
                snake[0].position.x += speed.x;
                snake[0].position.y += speed.y;
    
            }
            else snake[i].position = snakePosition[i-1];
                   
            if (snake[0].position.x == food.position.x && snake[0].position.y == food.position.y && food.active == true)
            {
                food.active = false;
                snake[counterTail].position = snakePosition[counterTail - 1];

                if (counterTail%7==0) snake[counterTail].colour = RED;
                else if (counterTail%6==0) snake[counterTail].colour = ORANGE;
                else if (counterTail%5==0) snake[counterTail].colour = YELLOW;
                else if (counterTail%4==0) snake[counterTail].colour = GREEN;
                else if (counterTail%3==0) snake[counterTail].colour = BLUE;
                else if (counterTail%2==0) snake[counterTail].colour = MAGENTA;
                else snake[counterTail].colour = PURPLE;

                for (int j = 0; j < counterTail; j++)
                {
                    while (snake[j].position.x == food.position.x && snake[j].position.y == food.position.y)
                    {
                        food.position = GetRandomPos();
                    }
                }
                counterTail++;
            } 
        }
        food.active = true;
    }

    //Check self eat
    for (int i = 1; i < counterTail; i++)
    {
        if (snake[i].position.x == snake[0].position.x && snake[i].position.y == snake[0].position.y)
        {
            run = false;
        }
    }

    //Wall
    if (snake[0].position.x < 0) snake[0].position.x = 360;
    else if (snake[0].position.y < 0) snake[0].position.y = 360;
    else if (snake[0].position.x > 360) snake[0].position.x = 0;
    else if (snake[0].position.y > 360) snake[0].position.y = 0;

    framescounter++;
}   

void Draw()
{
    BeginDrawing();
        ClearBackground(BLACK);
        //Draw Food
        DrawRectangleV(food.position,(Vector2){blockSize,blockSize},food.colour);
        for (int i = 0; i < counterTail; i++)
        {
            DrawRectangleV(snake[i].position,(Vector2){blockSize,blockSize},snake[i].colour);
            //cout<<counterTail<<endl;
        }
    EndDrawing();
}

void Check_controls()
{
    if (IsKeyPressed(KEY_UP) && speed.y != 40)
    {
        speed.x = 0;
        speed.y = -40;
    }
    else if (IsKeyPressed(KEY_DOWN) && speed.y != -40)
    {
        speed.x = 0;
        speed.y = 40;
    }
    else if (IsKeyPressed(KEY_LEFT) && speed.x != 40)
    {
        speed.x = -40;
        speed.y = 0;
    }
    else if (IsKeyPressed(KEY_RIGHT) && speed.x != -40)
    {
        speed.x = 40;
        speed.y = 0;
    }
}

Vector2 GetRandomPos()
{
    float x = GetRandomValue(0,9)*blockSize;
    float y = GetRandomValue(0,9)*blockSize;
    Vector2 randompos = {x,y};

    return randompos;
}