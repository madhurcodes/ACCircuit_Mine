#include <stdio.h>
#include "myheader.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern FILE* yyout;

///// Definitions

//
void AddComponent(char *name, char *net1, char *net2 ,float num, char *multiplier){

    printf("addd");
}
void AddSource(char *name, char *net1, char *net2, float dcOffset, float amplitude, float frequency, char* multiplier, float delay){
    printf("sourcee");

}

int main(int argc, char *argv[]) {
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
//    yyin = fopen(argv[1],"r");
//    //yyout = fopen(argv[2],"w+");
//    yyparse();
    return 0;
}