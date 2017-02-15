#include <stdio.h>


///// Definitions
typedef struct {

} edgeInfo;
typedef struct edgeList edgeList;
typedef struct {

    char **netName;
    edgeList *myEdgeList;

} vertice;
typedef struct {
    vertice *v1;
    vertice *v2;
    edgeInfo *info;


} edge;

typedef struct edgeListNode {

    edge *myEdge;
    struct edgeListNode *next;

} edgeListNode;
typedef struct edgeList {

    edgeListNode *head;

} edgeList;

typedef struct {

    vertice *myVetice;
    struct adjListNode *next;


} adjListNode;


typedef struct {
    adjListNode *head;
} adjList;


typedef struct {

    edgeList* myEdgeList;
    adjList*  myAdjList;

} graph;


// Definitions END

graph *newGraph(){

}

int main(){


    printf("dddd");
    return 0;
}