#include <stdlib.h>
#include "pathfinding.h"
#include "astar.h"
#include "snake.h"
#include "utils.h"

/**
 * Find the direction where the path to the tail is the longest
 * @param {Snake} snake -
 * @param {Path} path - path struct where the path founded is writed
 */
void longestPath(Snake *snake, Path *path){
    path->sizePath = 0;
    Pos next = {0, 0};
    Pos headPosition = snake->snakePosition[0];
    int dis = -1;
    for (int i = 0; i < 4; i++){
        next.x = headPosition.x + directions[i].x;
        next.y = headPosition.y + directions[i].y;

        if (next.x < 0 || next.x >= snake->width || next.y < 0 || next.y >= snake->length){
            continue;
        }
        Snake newSnake; 
        static Path direction ;
        direction.sizePath = 1;
        direction.arrPos[0] = directions[i];
        vSnake(snake, &direction, &newSnake);

        if (newSnake.dead == 1){
            continue;
        }

        static Path pathToTail ;
        astar(&newSnake, &pathToTail, 1, 0);
        if (pathToTail.sizePath > 0 && pathToTail.sizePath > dis){
            path->arrPos[0] = directions[i];
            path->sizePath = 1;
            dis = pathToTail.sizePath;
        }

    }
    return;
}

/**
 * Find a path to the food if it exist, else the longest path to the tail else the direction of the snake
 * @param {Snake} snake -
 * @param {Path} path - path struct where the path founded is writed
 */
void findPath(Snake *snake, Path *path){
    astar(snake, path, 0, 1);
    if (path->sizePath > 0){
        return;
    }
    

    longestPath(snake, path);
    if (path->sizePath > 0){
        return;
    }
    

    path->sizePath = 1;
    path->arrPos[0] = snake->direction;
    return; 
}