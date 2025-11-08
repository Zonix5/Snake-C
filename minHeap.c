// source : https://www.geeksforgeeks.org/c/c-program-to-implement-min-heap/

#include <stdlib.h>
#include "minHeap.h"
#include "utils.h"

void createHeap(Heap *h, Node *startNode){
    h->arr[0].node = startNode;
    h->arr[0].fCost = startNode->fCost;
    h->size = 1;
    h->capacity = LIST_MAX_SIZE;
    return ;
}

void insert(Heap* h, Node *node){
    if (h->size < h->capacity){
        h->arr[h->size].fCost = node->fCost;
        h->arr[h->size].node = node;
        insertHelper(h, h->size);
        h->size++;
    }
}

void removeNode(Heap* h, int index) {
    if (index >= h->size || index < 0) {
        return;
    }

    h->arr[index] = h->arr[h->size - 1];
    h->size--;

    // Réorganise le heap
    if (index > 0 && h->arr[index].fCost < h->arr[(index - 1) / 2].fCost) {
        insertHelper(h, index);
    } else {
        heapify(h, index);
    }
}

Node* extractMin(Heap* h){
    Node *deleteItem = NULL;
    if (h->size == 0){
        exit(EXIT_FAILURE);
    }
    deleteItem = h->arr[0].node;
    h->arr[0] = h->arr[h->size-1];
    h->size--;
    heapify(h, 0);
    return deleteItem;
}

void insertHelper(Heap* h, int index){
    int parent = (index - 1) / 2;

    int shouldSwap = 0;
    if (h->arr[parent].fCost > h->arr[index].fCost) {
        shouldSwap = 1;
    } else if (h->arr[parent].fCost == h->arr[index].fCost && 
               h->arr[parent].node->hCost > h->arr[index].node->hCost) {
        shouldSwap = 1;
    }
    
    if (shouldSwap) {
        NodeInfo temp = h->arr[parent];
        h->arr[parent] = h->arr[index];
        h->arr[index] = temp;
        insertHelper(h, parent);
    }
}

void heapify(Heap* h, int index){
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int min = index;

    if (left >= h->size || left < 0)
        left = -1;
    if (right >= h->size || right < 0)
        right = -1;

    if (left != -1) {
        if (h->arr[left].fCost < h->arr[index].fCost) {
            min = left;
        } else if (h->arr[left].fCost == h->arr[index].fCost && 
                   h->arr[left].node->hCost < h->arr[index].node->hCost) {
            min = left;
        }
    }
    
    if (right != -1) {
        if (h->arr[right].fCost < h->arr[min].fCost) {
            min = right;
        } else if (h->arr[right].fCost == h->arr[min].fCost && 
                   h->arr[right].node->hCost < h->arr[min].node->hCost) {
            min = right;
        }
    }
    
    if (min != index){
        NodeInfo temp = h->arr[min];
        h->arr[min] = h->arr[index];
        h->arr[index] = temp;
        heapify(h, min);
    }
}

