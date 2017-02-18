#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "myheader.h"



// Definitions END
// List

int indexInAdjList(adjList *a, char **name){
    int temp = 0;
    if(a == NULL){
        return NULL;
    }
    else{
        adjListNode *curr = a->head;
        while(curr != NULL) {
            if (strcmp(*(curr->myVetice->netName), *name) == 0) {
                return temp;
            }
            else{
                curr = curr->next;
                temp++;
            }
        }
        return  NULL;
    }
}

int indexInEdgeList(edgeList *a, char *name){
    int temp = 0;

    if(a == NULL){
        return NULL;
    }
    else{
        edgeListNode *curr = a->head;
        while(curr != NULL) {
            if (strcmp((curr->myEdge->info->name), name) == 0) {
                return temp;
            }
            else{
                curr = curr->next;
                temp++;

            }
        }
        return  NULL;
    }
}

void printEdge(edge *a){
    printf(" %s (", a->info->name);
    printf(" %c ", a->info->type);
    printf(" of %.16f between ", a->info->val);
    printf(" %s and", *a->v1->netName);
    printf(" %s ) ", *a->v2->netName);
}
void adjListInsert(adjList *a, vertice *b){
    // Inserts at Head
    a->size += 1;
    adjListNode *toInsert = (adjListNode *) calloc(1,sizeof(adjListNode));
    toInsert->myVetice = b;
    if(a->head == NULL){
        a->head = toInsert;
    }
    else{
        toInsert->next = a->head;
        a->head = toInsert;
    }
}

vertice *findInAdjList(adjList *a, char *name){
    if(a == NULL){
        return NULL;
    }
    else{
        adjListNode *curr = a->head;
        while(curr != NULL) {
            if (strcmp(*(curr->myVetice->netName), name) == 0) {
                return curr->myVetice;
            }
            else{
                curr = curr->next;
            }
        }
        return  NULL;
    }
}
vertice *getInAdjList(adjList *a, int ss){
    int temp = 0;
    if(a == NULL){
        return NULL;
    }
    else{
        adjListNode *curr = a->head;
        while(curr != NULL) {
            if (ss == temp) {
                return curr->myVetice;
            }
            else{
                curr = curr->next;
                temp++;
            }
        }
        return  NULL;
    }
}
edge *getInEdgeList(edgeList *a, int ss){
    int temp = 0;
    if(a == NULL){
        return NULL;
    }
    else{
        edgeListNode *curr = a->head;
        while(curr != NULL) {
            if (ss == temp) {
                return curr->myEdge;
            }
            else{
                curr = curr->next;
                temp++;
            }
        }
        return  NULL;
    }
}
void printAdjList(adjList *a){
    printf("\nAdjList has - ");
    adjListNode *t;
    if(a->head==NULL){
        return;
    }
    else{
        t = a->head;
        while(t!=NULL) {
            printf("%s ", *(t->myVetice->netName));
            t = t->next;
        }
    }
}

//
void edgeListInsert(edgeList *a, edge *b){
    // Inserts at Head
    edgeListNode *toInsert = (edgeListNode *) calloc(1,sizeof(edgeListNode));
    a->size += 1;
    toInsert->myEdge = b;
    if(a->head == NULL){
        a->head = toInsert;
    }
    else{
        toInsert->next = a->head;
        a->head = toInsert;
    }
}
edge *findInEdgeList(edgeList *a, char *name){
    if(a == NULL){
        return NULL;
    }
    else{
        edgeListNode *curr = a->head;
        while(curr != NULL) {
            if (strcmp((curr->myEdge->info->name), name) == 0){
                return curr->myEdge;
            }
            else{
                curr = curr->next;
            }
        }
        return  NULL;
    }
}

void printEdgeList(edgeList *a){
    printf("\nEdgeList has - ");
    edgeListNode *t;
    if(a->head==NULL){
        return;
    }
    else{
        t = a->head;
        while(t!=NULL) {
         //   printf("%s ", (t->myEdge->info->name));
            printEdge(t->myEdge);
            t = t->next;
        }
    }
}

edge *newEdge(vertice *i1, vertice *i2, float n, char *namee , char typ, char* stuff){
    edge *a = (edge *) calloc(1, sizeof(edge));
    a->info = (edgeInfo *) calloc(1, sizeof(edgeInfo));
    a->v1  = i1;
    a->v2 = i2;
    a->info->type = typ;
    a->info->val = n;
    a->info->stringed = stuff;
    a->info->name = (char *) calloc(strlen(namee),sizeof('a'));
    strcpy(a->info->name, namee);
    return  a;
}
//List Methods end
graph *newGraph() {

    graph *n = (graph *) malloc(sizeof(graph));
    n->myAdjList = (adjList *) calloc(1,sizeof(adjList));
    n->myAdjList->size =0;
    n->myEdgeList = (edgeList *) calloc(1,sizeof(edgeList));
    n->myEdgeList->size = 0;
    return n;
}

vertice *newVertice(char *b){
    vertice *a = (vertice *) calloc(1,sizeof(vertice));
    a->netName = (char **) calloc(1,sizeof(a->netName));
    a->myEdgeList = (edgeList *) calloc(1,sizeof(edgeList));
    *(a->netName) = b;
    return  a;
}
