#ifndef DEF_PATHFINDING
#define DEF_PATHFINDING
#include "astar.h"
#include "snake.h"
#include "utils.h"

#ifdef __cplusplus
extern "C" {
#endif

void longestPath(Snake *snake, Path *path);
void findPath(Snake *snake, Path *path);

#ifdef __cplusplus
}
#endif

#endif