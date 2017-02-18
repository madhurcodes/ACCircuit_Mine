#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "myheader.h"
#include <math.h>
///// Definitions
extern FILE * yyin;
extern  int yyparse();

graph *circuit;


void AddComponent(char *name, char *net1, char *net2 ,float num, char *multiplier){
    // Resistor - R, K
    // Capacitor -
    //
    // F, P, N , M , K, MEG, U
    //
   // printf("\n %s %f", name, num);
    char type;
    float nn = num;
    vertice *a, *b;
    if(findInAdjList(circuit->myAdjList,net1) == NULL ){
        a = newVertice(net1);
        adjListInsert(circuit->myAdjList, a);
    }
    else{
        a= findInAdjList(circuit->myAdjList,net1);
    }
    if(findInAdjList(circuit->myAdjList,net2) == NULL ){
        b = newVertice(net2);
        adjListInsert(circuit->myAdjList, b);
    }
    else{
        b = findInAdjList(circuit->myAdjList,net2);
    }
    if(strcmp(multiplier,"FF") == 0 ){
        type = 'C';
        nn *= powf(10,-15);
    }
    else if(strcmp(multiplier,"PF") == 0 ){
        type = 'C';
        nn *= powf(10,-12);
    }
    else if(strcmp(multiplier,"NF") == 0 ){
        type = 'C';
        nn *= powf(10,-9);

    }
    else if(strcmp(multiplier,"MF") == 0 ){
        type = 'C';
        nn *= powf(10,-3);

    }
    else if(strcmp(multiplier,"KF") == 0 ){
        type = 'C';
        nn *= powf(10,3);

    }
    else if(strcmp(multiplier,"MEGF") == 0 ){
        type = 'C';
        nn *= powf(10,6);

    }
    else if(strcmp(multiplier,"UF") == 0 ){
        type = 'C';
        nn *= powf(10,-6);

    }
    else if(strcmp(multiplier,"F") == 0 ){
        type = 'C';
    }
    else if(strcmp(multiplier,"FH") == 0 ){
        type = 'L';
        nn *= powf(10,-15);

    }
    else if(strcmp(multiplier,"PH") == 0 ){
        type = 'L';
        nn *= powf(10,-12);

    }
    else if(strcmp(multiplier,"NH") == 0 ){
        type = 'L';
        nn *= powf(10,-9);

    }
    else if(strcmp(multiplier,"UH") == 0 ){
        type = 'L';
        nn *= powf(10,-6);

    }
    else if(strcmp(multiplier,"MH") == 0 ){
        type = 'L';
        nn *= powf(10,-3);

    } else if(strcmp(multiplier,"KH") == 0 ){
        type = 'L';
        nn *= powf(10,3);

    }
    else if(strcmp(multiplier,"MEGH") == 0 ){
        type = 'L';
        nn *= powf(10,6);

    }
    else if(strcmp(multiplier,"H") == 0 ){
        type = 'L';

    }
    else if(strcmp(multiplier,"R") == 0 ){
        type = 'R';

    }
    else if(strcmp(multiplier,"P") == 0 ){
        type = 'R';
        nn *= powf(10,-12);

    }
    else if(strcmp(multiplier,"N") == 0 ){
        type = 'R';
        nn *= powf(10,-9);

    }else if(strcmp(multiplier,"U") == 0 ){
        type = 'R';
        nn *= powf(10,-6);

    }else if(strcmp(multiplier,"M") == 0 ){
        type = 'R';
        nn *= powf(10,-3);

    }else if(strcmp(multiplier,"K") == 0 ){
        type = 'R';
        nn *= powf(10,3);

    }else if(strcmp(multiplier,"MEG") == 0 ){
        type = 'R';
        nn *= powf(10,6);
    }
    else{
        printf("One Line in Input is Wrong");
        return;
    }
    edge *e = newEdge(a,b,nn,name,type);
    edgeListInsert(circuit->myEdgeList,e);
    edgeListInsert(e->v1->myEdgeList, e);
    edgeListInsert(e->v2->myEdgeList, e);
   // printf("%s %s %s %f %s\n", name, net1, net2, num, multiplier );
}
void AddSource(char *name, char *net1, char *net2, float dcOffset, float amplitude, float frequency, char* multiplier, float delay){
    printf("sourcee");
    // ad net1 and net2 to netlist if not already
    float nn = frequency;
    vertice *a, *b;
    if(findInAdjList(circuit->myAdjList,net1) == NULL ){
        a = newVertice(net1);
        adjListInsert(circuit->myAdjList, a);
    }
    else{
        a= findInAdjList(circuit->myAdjList,net1);
    }
    if(findInAdjList(circuit->myAdjList,net2) == NULL ){
        b = newVertice(net2);
        adjListInsert(circuit->myAdjList, b);
    }
    else{
        b = findInAdjList(circuit->myAdjList,net2);
    }
    if(strcmp(multiplier,"HZ") == 0 ){
    }
    else if(strcmp(multiplier,"KHZ") == 0 ){
        nn *= powf(10,3);
    }
    else if(strcmp(multiplier,"MEGHZ") == 0 ){
        nn *= powf(10,6);

    }
    else if(strcmp(multiplier,"NHZ") == 0 ){
        nn *= powf(10,-9);

    }
    else if(strcmp(multiplier,"UHZ") == 0 ){
        nn *= powf(10,-6);

    }
    else if(strcmp(multiplier,"MHZ") == 0 ){
        nn *= powf(10,-3);

    }
    else if(strcmp(multiplier,"PHZ") == 0 ){
        nn *= powf(10,-12);

    }
    else if(strcmp(multiplier,"FHZ") == 0 ){
        nn *= powf(10,-15);

    }
    else{
        printf("One Line in Input is Wrong");
        return;
    }
    edge *e = newEdge(a,b,nn,name,'S');
    e->info->isSource = 1;
    e->info->offSet = dcOffset;
    e->info->amplitude = amplitude;
    edgeListInsert(circuit->myEdgeList,e);
    edgeListInsert(e->v1->myEdgeList, e);
    edgeListInsert(e->v2->myEdgeList, e);
}

int main(int argc, char *argv[]) {
circuit = newGraph();
//    vertice *a = newVertice("mad");
//    vertice *b = newVertice("crazy");
//    vertice *e = newVertice("hazy");
//    adjListInsert(mg->myAdjList,a);
//    adjListInsert(mg->myAdjList,b);
//    adjListInsert(mg->myAdjList,e);
//    printAdjList(mg->myAdjList);
//    vertice *c = findInAdjList(mg->myAdjList, "mad");
//    printf("\n%s\n",*c->netName);
//    printf("\ndddd\n");
//    edge *me = newEdge(a,b,100,"--mad<->crazy--",'a');
//    edge *me2 = newEdge(b,e,100,"--hazy<->crazy--",'b');
//    addEdge(mg, me);
//    addEdge(mg,me2);
//    printf("\nAll edgesd\n");
//    printEdgeList(mg->myEdgeList);
//    printf("\nE's  edgesd\n");
//    printEdgeList(b->myEdgeList);
    yyin = fopen("in.txt","r");
    //yyout = fopen(argv[2],"w+");
    yyparse();
    printEdgeList(circuit->myEdgeList);
    printAdjList(circuit->myAdjList);
    return 0;
}