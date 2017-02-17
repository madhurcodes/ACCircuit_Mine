#include <stdio.h>
#include <malloc.h>
#include <string.h>

///// Definitions
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


// Definitions END
// List methods
void adjListInsert(adjList *a, vertice *b){
    // Inserts at Head
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

void printAdjList(adjList *a){
    printf("AdjList has - ");
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
            printf("%s ", (t->myEdge->info->name));
            t = t->next;
        }
    }
}

edge *newEdge(vertice *i1, vertice *i2, float n, char *namee , char typ){
    edge *a = (edge *) calloc(1, sizeof(edge));
    a->info = (edgeInfo *) calloc(1, sizeof(edgeInfo));
    a->v1  = i1;
    a->v2 = i2;
    a->info->type = typ;
    a->info->val = n;
    a->info->name = (char *) calloc(strlen(namee),sizeof('a'));
    strcpy(a->info->name, namee);
    return  a;
}
//List Methods end
graph *newGraph() {

    graph *n = (graph *) malloc(sizeof(graph));
    n->myAdjList = (adjList *) calloc(1,sizeof(adjList));
    n->myEdgeList = (edgeList *) calloc(1,sizeof(edgeList));
    return n;
}

vertice *newVertice(char *b){
    vertice *a = (vertice *) calloc(1,sizeof(vertice));
    a->netName = (char **) calloc(1,sizeof(a->netName));
    a->myEdgeList = (edgeList *) calloc(1,sizeof(edgeList));
    *(a->netName) = b;
    return  a;
}
void *addEdge(graph *a, edge *b){
    edgeListInsert(a->myEdgeList,b);
    edgeListInsert(b->v1->myEdgeList, b);
    edgeListInsert(b->v2->myEdgeList, b);
}
int main() {
    graph *mg = newGraph();
    vertice *a = newVertice("mad");
    vertice *b = newVertice("crazy");
    vertice *e = newVertice("hazy");
    adjListInsert(mg->myAdjList,a);
    adjListInsert(mg->myAdjList,b);
    adjListInsert(mg->myAdjList,e);
    printAdjList(mg->myAdjList);
    vertice *c = findInAdjList(mg->myAdjList, "mad");
    printf("\n%s\n",*c->netName);
    printf("\ndddd\n");
    edge *me = newEdge(a,b,100,"--mad<->crazy--",'a');
    edge *me2 = newEdge(b,e,100,"--hazy<->crazy--",'b');
    addEdge(mg, me);
    addEdge(mg,me2);
    printf("\nAll edgesd\n");
    printEdgeList(mg->myEdgeList);
    printf("\nE's  edgesd\n");
    printEdgeList(b->myEdgeList);
    return 0;
}