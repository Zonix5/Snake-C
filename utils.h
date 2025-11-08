#ifndef DEF_UTILS
#define DEF_UTILS
#define LIST_MAX_SIZE 50
#define SNAKE_MAX_SIZE 256

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Pos Pos;
struct Pos{
    int x;
    int y;
};

extern Pos directions[4];

typedef struct Path Path;
struct Path{
    Pos arrPos[LIST_MAX_SIZE];
    int sizePath;
};

typedef struct Node Node;
struct Node{
    Pos pos;
    Pos snakePos[SNAKE_MAX_SIZE];
    Pos direction;
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