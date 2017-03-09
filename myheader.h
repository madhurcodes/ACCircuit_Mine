/*Header file to use functions externally*/

//
// Created by Madhur on 2/17/2017.
//

#ifndef ACCIRCUIT_MYHEADER_H
#define ACCIRCUIT_MYHEADER_H
#endif //ACCIRCUIT_MYHEADER_H
#include <stdio.h>

int invert();
typedef struct
{
    char *name;
    float val;
    char type;
    int isSource;
    float offSet;
    float amplitude;
    float delay;
    char *stringed;
} edgeInfo;

typedef struct edgeList edgeList;

typedef struct vertice
{
    char **netName;
    float v_real;
    float v_imag;
    edgeList *myEdgeList;

} vertice;
typedef struct 
{
    vertice *v1;
    vertice *v2;
    edgeInfo *info;
    float i_real;
    float i_imag;
    float z_real;
    float z_imag;
} edge;

typedef struct edgeListNode
{
    edge *myEdge;
    struct edgeListNode *next;
} edgeListNode;

typedef struct edgeList
{
    edgeListNode *head;
    int size;
} edgeList;

typedef struct adjListNode 
{
    vertice *myVetice;
    struct adjListNode *next;
} adjListNode;

typedef struct adjList 
{
    int size;
    adjListNode *head;
} adjList;

typedef struct 
{
    edgeList *myEdgeList;
    adjList *myAdjList;
} graph;



void adjListInsert (adjList *a, vertice *b);
vertice *findInAdjList (adjList *a, char *name);
void printAdjList ( adjList *a);
void edgeListInsert ( edgeList *a, edge *b);
edge *findInEdgeList (edgeList *a, char *name);
void printEdgeList (edgeList *a);
edge *newEdge (vertice *i1, vertice *i2, float n, char *namee , char typ, char *stuff);
graph *newGraph () ;
vertice *newVertice (char *b);
void *addEdge (graph *a, edge *b);
vertice *getInAdjList(adjList *a, int ss);
edge *getInEdgeList(edgeList *a, int ss);
int indexInAdjList(adjList *a, char **name);
int indexInEdgeList(edgeList *a, char *name);
int neighboursof(vertice* v);
edge *edgesfrom(vertice* v, int a);