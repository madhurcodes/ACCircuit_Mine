/*File that contains all function definitions of Graph*/


#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "myheader.h"
/* Note - All struct definitions and function prototypes are in myheader.h*/


/*Function to get the index of an element in the vertex list */
int indexInAdjList(adjList *a, char **name)
{
    /*A simple implementation with a counter and moving to next.*/
    int temp = 0;
    if(a == NULL)
    {
        return -1;
    }
    else
    {
        adjListNode *curr = a->head;
        while(curr != NULL) 
        {
            if (strcmp(*(curr->myVetice->netName), *name) == 0)
            {
                return temp;
            }
            else
            {
                curr = curr->next;
                temp++;
            }
        }
        return  -1;
    }
}

/*Function to get the index of an element in the edge list */
int indexInEdgeList(edgeList *a, char *name)
{
    int temp = 0;
    if(a == NULL)
    {
        return -1;
    }
    else
    {
        edgeListNode *curr = a->head;
        while(curr != NULL) 
        {
            if (strcmp((curr->myEdge->info->name), name) == 0) 
            {
                return temp;
            }
            else
            {
                curr = curr->next;
                temp++;
            }
        }
        return  -1;
    }
}

/*print  values stored in an edge (ie a component) */
void printEdge(edge *a)
{
    printf(" %s (", a->info->name);
    printf(" %c ", a->info->type);
    printf(" of %.16f between ", a->info->val);
    printf(" %s and", *a->v1->netName);
    printf(" %s ) ", *a->v2->netName);
}

/*Insert new element at the head of the list*/
void adjListInsert(adjList *a, vertice *b)
{
    a->size += 1;
    adjListNode *toInsert = (adjListNode *) calloc(1,sizeof(adjListNode));
    toInsert->myVetice = b;
    adjListNode* temp = a->head;
    if(a->head == NULL)
    {
        a->head = toInsert;
    }
    else
    {
        while(temp->next!=NULL){
            temp=temp->next;
        }
        toInsert->next = NULL;
        temp->next = toInsert;
    }
}

/*Search for a net name in vertices list*/
vertice *findInAdjList(adjList *a, char *name)
{
    if(a == NULL)
    {
        return NULL;
    }
    else
    {
        adjListNode *curr = a->head;
        while(curr != NULL) 
        {
            if (strcmp(*(curr->myVetice->netName), name) == 0) 
            {
                return curr->myVetice;
            }
            else
            {
                curr = curr->next;
            }
        }
        return  NULL;
    }
}

/*get the nth element of the vertex list*/

vertice *getInAdjList(adjList *a, int ss)
{
    int temp = 0;
    if(a == NULL)
    {
        return NULL;
    }
    else
    {
        adjListNode *curr = a->head;
        while(curr != NULL) 
        {
            if (ss == temp) 
            {
                return curr->myVetice;
            }
            else
            {
                curr = curr->next;
                temp++;
            }
        }
        return  NULL;
    }
}

/*get the nth element of the edge list*/
edge *getInEdgeList(edgeList *a, int ss)
{
    int temp = 0;
    if(a == NULL)
    {
        return NULL;
    }
    else{
        edgeListNode *curr = a->head;
        while(curr != NULL)
        {
            if (ss == temp) 
            {
                return curr->myEdge;
            }
            else
            {
                curr = curr->next;
                temp++;
            }
        }
        return  NULL;
    }
}

/*print  values stored in an vertex */
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

/*Function to insert a edge in edge list at the head*/
void edgeListInsert(edgeList *a, edge *b)
{
    edgeListNode *toInsert = (edgeListNode *) calloc(1,sizeof(edgeListNode));
    a->size += 1;
    edgeListNode *temp = a->head;
    toInsert->myEdge = b;
    if(a->head == NULL)
    {
        a->head = toInsert;
    }
    else
    {
        while(temp->next!=NULL){
            temp=temp->next;
        }
        toInsert->next = NULL;
        temp->next = toInsert;
    }
}

/* To FInd elemts in the edge list.*/
edge *findInEdgeList(edgeList *a, char *name)
{
    if(a == NULL)
    {
        return NULL;
    }
    else{
        edgeListNode *curr = a->head;
        while(curr != NULL) 
        {
            if (strcmp((curr->myEdge->info->name), name) == 0)
            {
                return curr->myEdge;
            }
            else
            {
                curr = curr->next;
            }
        }
        return  NULL;
    }
}

/*function to print edge values*/

void printEdgeList(edgeList *a)
{
    printf("\nEdgeList has - ");
    edgeListNode *t;
    if(a->head==NULL)
    {
        return;
    }
    else
    {
        t = a->head;
        while(t!=NULL) 
        {
            printEdge(t->myEdge);
            t = t->next;
        }
    }
}

/*Function to create a new edge*/
edge *newEdge(vertice *i1, vertice *i2, float n, char *namee , char typ, char* stuff)
{
    edge *a = (edge *) calloc(1, sizeof(edge));
    a->info = (edgeInfo *) calloc(1, sizeof(edgeInfo));
    a->v1  = i1;
    a->v2 = i2;
    a->info->type = typ;
    a->info->val = n;
    a->info->stringed = stuff;
    a->info->name = (char *) calloc(strlen(namee),sizeof('a'));
    strcpy(a->info->name, namee);
    a->i_real=0;
    a->i_imag=0;
    a->z_real=0;
    a->z_imag=0;
    return  a;
}

/*Function to initialise a new graph*/
graph *newGraph() 
{
    graph *n = (graph *) malloc(sizeof(graph));
    n->myAdjList = (adjList *) calloc(1,sizeof(adjList));
    n->myAdjList->size =0;
    n->myEdgeList = (edgeList *) calloc(1,sizeof(edgeList));
    n->myEdgeList->size = 0;
    return n;
}

/*Function to create a new vertex*/
vertice *newVertice(char *b)
{
    vertice *a = (vertice *) calloc(1,sizeof(vertice));
    a->netName = (char **) calloc(1,sizeof(a->netName));
    a->myEdgeList = (edgeList *) calloc(1,sizeof(edgeList));
    *(a->netName) = b;
    a->v_real = 0;
    a->v_imag = 0;
    return  a;
}
int neighboursof(vertice* v){
    return v->myEdgeList->size;
}
edge *edgesfrom(vertice* v, int a){
    return getInEdgeList(v->myEdgeList,a);
}
