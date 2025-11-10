#include <stdlib.h>
#include "astar.h"
#include "snake.h"
#include "minHeap.h"
#include "hashTable.h"
#include "utils.h"

/**
 * Return the manhattan distance of 2 position in a 2D space
 * https://www.geeksforgeeks.org/data-science/manhattan-distance/
 * @param {Pos} a - first position
 * @param {Pos} b - second position
 * @return {int} - the manhattan distance of the 2 position
 */
int manhattanDistance(Pos a, Pos b){
    return abs(b.x - a.x) + abs(b.y - a.y);
}

/**
 * Find a path to the food using the A* algorithm
 * https://www.geeksforgeeks.org/dsa/a-search-algorithm/
 * 
 * @param {Snake} snake
 * @param {Path} path - path struct where the path founded is writed
 * @param {int} tail - set the goal at the end of the snake
 * @param {int} move - set if the snake grow or not when it move 
 */
void astar(Snake *snake, Path *path, int tail, int move){
    // definir la taille maximum du path : 2 fois la taille de la matrice de led
    int maxG = snake->length * snake->width * 2;
    // position de depart : la tete du serpent
    Pos start = snake->snakePosition[0];
    Pos goal;
    if (tail){
        // on va vers la queue
        goal = snake->snakePosition[snake->snakeSize-1];
    }
    else{
        goal = snake->foodPosition;
    }

    // Pre allouer tout les nodes en memoire et garder un index a celui ou on est
    Node nodePool[LIST_MAX_SIZE];
    int nodePoolSize = 0;

    HTNode closedListPool[HT_MAX_SIZE];
    int closedListSize = 0;

    // liste pour verifier si un node a deja ete visitÃ©
    HTNode* closedList[HT_MAX_SIZE] = {NULL};


    // creation du 1er node
    Node startNode;
    startNode.pos = start;
    for (int i = 0; i < snake->snakeSize; i++){
        startNode.snakePos[i] = snake->snakePosition[i];
    } 
    startNode.direction.x = 0;
    startNode.direction.y = 0;
    startNode.parent = NULL;
    startNode.snakeSize = snake->snakeSize;
    startNode.gCost = 0;
    startNode.hCost = manhattanDistance(start, goal);
    startNode.fCost = startNode.gCost + startNode.hCost;

    path->sizePath = 0;
    
    // liste qui garde toujour le node avec le cout le moin grande en 1er
    Heap minHeap; 
    createHeap(&minHeap, &startNode);

    while(minHeap.size > 0){
        // recuperer le node suivant et l'ajouter a la liste fermÃ©e
        Node *currentNode = extractMin(&minHeap);

        if (closedListSize >= HT_MAX_SIZE){
            path->sizePath = 0;
            return;
        }
        add(closedList, currentNode, closedListPool, &closedListSize, 1);
        
        // verifier que on est dans les limite de taille
        if (currentNode->gCost >= maxG){
            continue;
        }
        
        // si la position est celle de l'objectif
        if (currentNode->pos.x == goal.x && currentNode->pos.y == goal.y){
            while(currentNode->parent != NULL){
                // remonter les node precedent et mettre leur direction dans la liste
                path->sizePath++;
                path->arrPos[path->sizePath-1] = currentNode->direction;
                currentNode = currentNode->parent;
            }
            // inverser l'ordre de la liste pour etre dans le bon sens
            int startIndex = 0;
            int endIndex = path->sizePath-1;
            while (startIndex < endIndex){
                Direction temp = path->arrPos[startIndex];
                path->arrPos[startIndex] = path->arrPos[endIndex];
                path->arrPos[endIndex] = temp;
                startIndex++;
                endIndex--;
            }
            
            if (tail == 0){
                // verifier que il y a un acces a la queue, empeche le serpent de s'enfermÃ© sur lui meme
                Snake virtualSnake;
                Path tailPath;
                vSnake(snake, path, &virtualSnake);
                astar(&virtualSnake, &tailPath, 1, 0);
    
                if (tailPath.sizePath > 0){
                    return;
                }
                
                path->sizePath = 0;
                continue;
            }
            return;
        }
        // pour chaque direction (haut, bas, droite, gauche) une nouvelle position
        for (int i = 0; i < 4; i++){
            Pos next = {currentNode->pos.x + directions[i].x, currentNode->pos.y + directions[i].y};
            // verifier que on est dans les limites de la matrice de led
            if (next.x < 0 || next.x >= snake->width || next.y < 0 || next.y >= snake->length){
                continue;
            }

            // verifier que la nouvelle position n'est pas dans le corps du serpent (queue exclue car il avance)
            if (isIn(next, currentNode->snakePos, currentNode->snakeSize-1)){
                continue;
            }

            // recuperer un pointeur pour un nouveau node
            if (nodePoolSize >= LIST_MAX_SIZE){
                exit(EXIT_FAILURE);
            }
            Node *newNode = &nodePool[nodePoolSize];
            nodePoolSize++;

            // ajouter les informations au nouveau node
            newNode->pos.x = next.x;
            newNode->pos.y = next.y;

            for (int j = 0; j < currentNode->snakeSize; j++){
                newNode->snakePos[j] = currentNode->snakePos[j];
            }
            
            newNode->direction = directions[i];
            newNode->parent = currentNode;
            newNode->snakeSize = currentNode->snakeSize;
            newNode->gCost = currentNode->gCost + 1;
            newNode->hCost = manhattanDistance(newNode->pos, goal);
            newNode->fCost = newNode->gCost + newNode->hCost;

            if (move == 0){
                newNode->snakeSize++;
            }

            for (int i = newNode->snakeSize - 1; i > 0; i--){
                newNode->snakePos[i] = newNode->snakePos[i - 1];
            }
            newNode->snakePos[0] = newNode->pos;

            // verifier si le nouveau node n'a pas deja ete visite
            if (retrieve(closedList, newNode) != 0){
                continue;
            }
            
            // verifier si un node avec la meme position est deja dans la liste ouverte
            Node *existingNode = NULL;
            int j;
            for (j = 0; j < minHeap.size; j++){
                if(newNode->pos.x == minHeap.arr[j].node->pos.x && newNode->pos.y == minHeap.arr[j].node->pos.y){
                    existingNode = minHeap.arr[j].node;
                    break;
                }
            }

            // si non on ajoute le nouveau node dans la liste ouverte
            if (existingNode == NULL){
                insert(&minHeap, newNode);
            }

            // si oui on regarde si le cout g est plus petit que celui existant et on le remplace
            else if(newNode->gCost < existingNode->gCost){
                removeNode(&minHeap, j);
                insert(&minHeap, newNode);
            }

        }
    }
    return;
}