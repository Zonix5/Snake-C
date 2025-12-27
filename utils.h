#ifndef DEF_UTILS
#define DEF_UTILS

#include <stdint.h>

#define LIST_MAX_SIZE 10000
#define SNAKE_LENGTH 16
#define SNAKE_WIDTH 16

#define SNAKE_MAX_SIZE SNAKE_LENGTH*SNAKE_WIDTH

#ifdef __cplusplus
extern "C" {
#endif
 
typedef struct Pos Pos;
struct Pos{
    int8_t x; 
    int8_t y;
};

typedef struct Direction Direction;
struct Direction{
    int8_t x;
    int8_t y;
};

extern Direction directions[4];

typedef struct Path Path;
struct Path{
    Direction arrPos[SNAKE_MAX_SIZE*2];
    uint16_t sizePath;
};

typedef struct Node Node;
struct Node{
    Pos pos;
    // Pos snakePos[SNAKE_MAX_SIZE];
    Direction direction;
    Node *parent;
    uint16_t snakeSize;
    uint16_t gCost;
    uint16_t hCost;
    uint16_t fCost;
};

#ifdef __cplusplus
}
#endif

#endif