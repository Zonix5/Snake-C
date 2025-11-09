#include <stdlib.h>
#include "hashTable.h"
#include "utils.h"

// https://www.geeksforgeeks.org/dsa/hash-table-data-structure/

/**
 * Compare 2 node based on their position and G cost
 * @param {Node} nodeA - first node
 * @param {Node} nodeB - seconde node
 * @return {int} - 1 if they are the same else 0
 */
int compareNode(Node *nodeA, Node *nodeB){
    return (nodeA->pos.x == nodeB->pos.x && 
            nodeA->pos.y == nodeB->pos.y &&
            nodeA->gCost == nodeB->gCost);
}

/**
 * Hash a node to get is index in the list
 * @param {Node} key
 * @return {int} - index of the node
 */
int hashFunction(Node *key) {
    unsigned int hash = 0;
    hash = hash * 33 + key->pos.x;
    hash = hash * 33 + key->pos.y;
    hash = hash * 33 + key->gCost;
    return hash % HT_MAX_SIZE;
}

/**
 * Add a node to the hash table
 * No collision detection
 * @param {HTNode} table - the hash table where the node is added
 * @param {Node} key - the node to add
 * @param {int} value - the value associated with the node
 */
void add(HTNode* table[], Node *key, int value) {
    int i = hashFunction(key);
    HTNode *n = table[i];
    n->key = key;
    n->value = value;
    n->next = table[i];
}

/**
 * look if a node is already in the table
 * @param {HTNode} table - the hash table
 * @param {Node} key - the node to check
 * @return {int} - 1 if a correspondant node is founded else 0
 */
int retrieve(HTNode *table[], Node *key) {
    HTNode *n = table[hashFunction(key)];
    
    while (n) {
        if (compareNode(n->key, key)) 
            return n->value;
        n = n->next;
    }
    
    return 0;
}