// source : https://www.geeksforgeeks.org/c/c-program-to-implement-min-heap/

#ifndef DEF_MINHEAP
#define DEF_MINHEAP
#include "utils.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct NodeInfo NodeInfo;
struct NodeInfo{
    Node *node;
    int fCost;
};

typedef struct Heap Heap;
struct Heap {
    NodeInfo arr[LIST_MAX_SIZE];
    int size;
    int capacity;
};

void createHeap(Heap *h, Node *startNode);
void insert(Heap* h, Node *node);
Node* extractMin(Heap* h);
void insertHelper(Heap* h, int index);
void heapify(Heap* h, int index);
void removeNode(Heap* h, int index);

#ifdef __cplusplus
}
#endif

#endif