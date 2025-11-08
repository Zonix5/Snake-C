#ifndef DEF_HASHTABLE
#define DEF_HASHTABLE
#define HT_MAX_SIZE 503

#include "utils.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct HTNode HTNode;
struct HTNode {
    Node *key;
    int value;
    struct HTNode *next;
};

int hashFunction(Node *key);
int compareNode(Node *nodeA, Node *nodeB);
void add(HTNode *table[], Node *key, int value);
int retrieve(HTNode *table[], Node *key);

#ifdef __cplusplus
}
#endif

#endif