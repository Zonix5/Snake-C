#ifndef DEF_UTILS
#define DEF_UTILS
#define LIST_MAX_SIZE 4500

#define SNAKE_LENGTH 16
#define SNAKE_WIDTH 16

#define SNAKE_MAX_SIZE SNAKE_LENGTH*SNAKE_WIDTH

#ifdef __cplusplus
extern "C" {
#endif
 
typedef struct Pos Pos;
struct Pos{
    int x;
    int y;
};

typedef struct Direction Direction;
struct Direction{
    int x;
    int y;
};

extern Direction directions[4];

typedef struct Path Path;
struct Path{
    Direction arrPos[SNAKE_MAX_SIZE];
    int sizePath;
};

typedef struct Node Node;
struct Node{
    Pos pos;
    // Pos snakePos[SNAKE_MAX_SIZE];
    Direction direction;
    Node *parent;
    int snakeSize;
    int gCost;
    int hCost;
    int fCost;
};

#ifdef __cplusplus
}
#endif

#endif
