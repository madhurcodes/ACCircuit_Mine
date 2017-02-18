//
// Created by Madhur on 2/17/2017.
//

#ifndef ACCIRCUIT_MYHEADER_H
#define ACCIRCUIT_MYHEADER_H
#endif //ACCIRCUIT_MYHEADER_H
#include <stdio.h>

 int yylex();
 int yyparse();
 FILE* yyin;
 FILE* yyout;

typedef struct {
    char *name;
    float val;
    char type;
} edgeInfo;
typedef struct edgeList edgeList;
typedef struct vertice {

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

typedef struct adjListNode {

    vertice *myVetice;
    struct adjListNode *next;


} adjListNode;


typedef struct adjList {
    adjListNode *head;
} adjList;


typedef struct {

    edgeList *myEdgeList;
    adjList *myAdjList;

} graph;
void adjListInsert (adjList *a, vertice *b);
vertice *findInAdjList (adjList *a, char *name);
void printAdjList ( adjList *a);
void edgeListInsert ( edgeList *a, edge *b);
edge *findInEdgeList (edgeList *a, char *name);
void printEdgeList (edgeList *a);
edge *newEdge (vertice *i1, vertice *i2, float n, char *namee , char typ);
graph *newGraph () ;
vertice *newVertice (char *b);
void *addEdge (graph *a, edge *b);