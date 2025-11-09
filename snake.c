#include <stdlib.h>
#include "esp_random.h"
#include "snake.h"
#include "utils.h"

/**
 * moves the snake forward
 * @param {Snake} snake -
 * @param {Pos} direction - the direction in which the snake is going
 */
void run(Snake *snake, Direction direction){
    snake->direction = direction;
    newHead(snake);

    if (isDead(snake)){
        snake->dead = 1;
        return;
    }

    int ateFood = (snake->snakeHead.x == snake->foodPosition.x && 
                   snake->snakeHead.y == snake->foodPosition.y);

    if (ateFood){
        snake->score += 1;
        snake->foodOnBoard = 0;
        snake->snakeSize += 1;  // Augmenter AVANT move
    }

    // DÃ©caler le serpent (en gardant la queue si ateFood)
    for (int i = snake->snakeSize - 1; i > 0; i--){
        snake->snakePosition[i] = snake->snakePosition[i - 1];
    }
    snake->snakePosition[0] = snake->snakeHead;
    
    if (!snake->foodOnBoard){
        setFood(snake);
    }
}

/**
 * Init the snake structure
 * @param {Snake} snake -
 */
void initSnake(Snake *snake){
    snake->dead = 0;
    snake->score = 0;

    snake->length = 16;
    snake->width = 16;

    snake->direction.x = 0;
    snake->direction.y = 1;

    snake->oldDirection.x = 0;
    snake->oldDirection.y = 1;

    snake->snakePosition[0].x = 0;
    snake->snakePosition[0].y = 2;

    snake->snakePosition[1].x = 0;
    snake->snakePosition[1].y = 1;

    snake->snakePosition[2].x = 0;
    snake->snakePosition[2].y = 0;

    snake->snakeSize = 3;

    snake->snakeHead.x = snake->snakePosition[0].x;
    snake->snakeHead.y = snake->snakePosition[0].y;

    snake->foodPosition.x = 0;
    snake->foodPosition.y = 0;
    setFood(snake);
}

/**
 * Check if a position is in a array of position
 * @param {Pos} position - the position to check
 * @param {Pos} array - the array of position
 * @param {int} size - the size of the array
 * @return {int} - 1 if the position is in the array else 0
 */
int isIn(Pos position, Pos array[], int size){
    for (int i = 0; i < size; i++){
        if (position.x == array[i].x && position.y == array[i].y){
            return 1;
        }
    }
    return 0;
}

/**
 * Set the food position
 * @param {Snake} snake -
 */
void setFood(Snake *snake) {
  Pos position;
  do {
    position.x = esp_random() % snake->length;
    position.y = esp_random() % snake->width;
    if (snake->score == 256-3){
            snake->dead = 1;
            position.x = -1;
            position.y = -1;
            break;
        }
  } while (isIn(position, snake->snakePosition, snake->snakeSize));
  snake->foodPosition = position;
  snake->foodOnBoard = 1;
}

/**
 * Check if 2 direction are opposite
 * @param {Pos} a - the first direction
 * @param {Pos} b - the seconde direction
 * @return {int} - 1 if they are opposite else 0
 */
int directionOpposite(Direction a, Direction b){
    return a.x == -b.x && a.y == -b.y;
}

/**
 * move the snake head to the actual direction
 * @param {Snake} snake -
 */
void newHead(Snake *snake){
    if (directionOpposite(snake->direction, snake->oldDirection)){
        snake->snakeHead.x = snake->snakePosition[0].x + snake->oldDirection.x;
        snake->snakeHead.y = snake->snakePosition[0].y + snake->oldDirection.y;
    }else{
        snake->oldDirection = snake->direction;
        snake->snakeHead.x = snake->snakePosition[0].x + snake->direction.x;
        snake->snakeHead.y = snake->snakePosition[0].y + snake->direction.y;
    }
}

/**
 * Change the side of the head if it's out of bound
 * @param {Snake} snake -
 */
void changeSide(Snake *snake){
    snake->snakeHead.x = ((snake->snakeHead.x % snake->width) + snake->width) % snake->width;
    snake->snakeHead.y = ((snake->snakeHead.y % snake->length) + snake->length) % snake->length;
}

/**
 * Shift all the position of the snake
 * @param {Snake} snake -
*/
void move(Snake *snake){
    for (int i = snake->snakeSize - 1; i > 0; i--){
        snake->snakePosition[i] = snake->snakePosition[i - 1];
    }
    snake->snakePosition[0] = snake->snakeHead;
}

/**
 * Check if the snake is dead
 * @param {Snake} snake -
 * @return {int} - 1 if he is dead else 0
 */
int isDead(Snake *snake){
    return (
    isIn(snake->snakeHead, snake->snakePosition, snake->snakeSize - 1) ||
    snake->snakeSize == 256 ||
    (snake->snakeHead.x < 0 || snake->snakeHead.x >= snake->width || snake->snakeHead.y < 0 || snake->snakeHead.y >= snake->length));
}

/**
 * Copy snake position into another and make it follow a path
 * @param {Snake} snake -
 * @param {Path} path - the path to follow
 * @param {Snake} virtualSnake - the new snake
 */
void vSnake(Snake *snake, Path *path, Snake *virtualSnake){

    virtualSnake->dead = snake->dead;
    virtualSnake->score = snake->score;
    virtualSnake->foodOnBoard = snake->foodOnBoard;
    virtualSnake->length = snake->length;
    virtualSnake->width = snake->width;
    virtualSnake->snakeSize = snake->snakeSize;
    virtualSnake->direction = snake->direction;
    virtualSnake->oldDirection = snake->oldDirection;
    virtualSnake->snakeHead = snake->snakeHead;
    virtualSnake->foodPosition = snake->foodPosition;

    for (int i = 0; i < snake->snakeSize; i++){
        virtualSnake->snakePosition[i] = snake->snakePosition[i];
    }

    for (int i = 0; i < path->sizePath; i++){
        run(virtualSnake, path->arrPos[i]);
    }
}