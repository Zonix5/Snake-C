#ifndef DEF_ASTAR
#define DEF_ASTAR
#include "utils.h"
#include "snake.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Snake Snake;

void astar(Snake *snake, Path *path, int tail, int move);
int manhattanDistance(Pos a, Pos b);
void getPos(Snake *snake, Node *node, Pos outputPos[], int *outputPosSize, int ouputPosMaxSize, int move);

#ifdef __cplusplus
}
#endif

#endif