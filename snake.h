#ifndef DEF_SNAKE
#define DEF_SNAKE
#include "utils.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Path Path;

typedef struct Snake Snake;
struct Snake{
    int dead;
    int score;
    int foodOnBoard;
    int length;
    int width;

    int snakeSize;

    Pos direction;
    Pos oldDirection;
    Pos snakePosition[SNAKE_MAX_SIZE];
    
    Pos snakeHead;
    Pos foodPosition;
};

void run(Snake *snake, Pos direction);

void initSnake(Snake *snake);
void setFood(Snake *snake);
void newHead(Snake *snake);
void changeSide(Snake *snake);
void move(Snake *snake);
int isDead(Snake *snake);
int directionOpposite(Pos a, Pos b);
int isIn(Pos position, Pos tableau[], int size);
void vSnake(Snake *snake, Path *path, Snake *virtualSnake);

#ifdef __cplusplus
}
#endif

#endif