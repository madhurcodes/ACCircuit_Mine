/*Main source file*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "myheader.h"
#include <math.h>
/* Definitions */
extern FILE * yyin;
extern  int yyparse();
FILE *output;
graph *circuit;

/*svg code for various symbols used*/ 

char capacitor[] = "<line x1=\"0\" y1=\"25\" x2=\"40\" y2=\"25\" \n"
"\tstroke-width=\"2\" stroke=\"black\" />\n"
"\t<line x1=\"40\" y1=\"0\" x2=\"40\" y2=\"50\" \n"
"\tstroke-width=\"2\" stroke=\"black\" />\n"
"\t<line x1=\"60\" y1=\"0\" x2=\"60\" y2=\"50\" \n"
"\tstroke-width=\"2\" stroke=\"black\" />\n"
"\t<line x1=\"60\" y1=\"25\" x2=\"100\" y2=\"25\" \n"
"\tstroke-width=\"2\" stroke=\"black\" />";

char inductor[] = "<path \n"
"     d=\"M 0,25 L 20,25 C 20,25 20,0 30,0 C 40,0 40,25 40,25 C 40,25 40,0 50,0 C 60,0 60,25 60,25 C 60,25 60,0 70,0 C 80,0 80,25 80,25 L 100,25\" stroke=\"black\" fill=\"none\" stroke-width=\"2\"/>\t" ;

char resistor[] = " <path d=\"M 0 25 L 25 25, 30 0, 40 50, 50 0, 60 50, 70 0, 75 25, 100 25\"\n"
"stroke=\"black\" fill=\"none\" stroke-width=\"2\"/>\t ";

char currentSource[] = "\n"
"<ellipse cx=\"50\" cy=\"25\" rx=\"25\" ry=\"25\"\n"
"\tstroke=\"black\" stroke-width=\"2\" fill=\"none\" />  \n"
"\t\n"
"<line x1=\"0\" y1=\"25\" x2=\"25\" y2=\"25\" \n"
"\tstroke-width=\"2\" stroke=\"black\" />\n"
"\n"
"<line x1=\"75\" y1=\"25\" x2=\"100\" y2=\"25\" \n"
"\tstroke-width=\"2\" stroke=\"black\" />\n"
"\n"
"<line x1=\"30\" y1=\"25\" x2=\"70\" y2=\"25\" \n"
"\tstroke-width=\"2\" stroke=\"black\" />\n"
"\n"
"<line x1=\"50\" y1=\"15\" x2=\"70\" y2=\"25\" \n"
"\tstroke-width=\"2\" stroke=\"black\" />\n"
"\n"
"<line x1=\"50\" y1=\"35\" x2=\"70\" y2=\"25\" \n"
"\tstroke-width=\"2\" stroke=\"black\" />";

char voltageSource[] = "<ellipse cx=\"50\" cy=\"25\" rx=\"25\" ry=\"25\"\n"
"\tstroke=\"black\" stroke-width=\"2\" fill=\"none\" />  \n"
"\t\n"
"<line x1=\"0\" y1=\"25\" x2=\"25\" y2=\"25\" \n"
"\tstroke-width=\"2\" stroke=\"black\" />\n"
"\n"
"<line x1=\"75\" y1=\"25\" x2=\"100\" y2=\"25\" \n"
"\tstroke-width=\"2\" stroke=\"black\" />\n"
"\n"
"<path \n"
"     d=\"M 30,25 C 30,25 30,10 40,10 C 50,10 50,25 50,25 C 50,25 50,40 60,40 C 70,40 70,25 70,25 L 70,25\" stroke=\"black\" fill=\"none\" stroke-width=\"2\"/>\t";

char ground[] = "\t<line x1=\"50\" y1=\"0\" x2=\"50\" y2=\"20\" \n"
"\tstroke-width=\"2\" stroke=\"black\" />\n"
"\t<line x1=\"20\" y1=\"20\" x2=\"80\" y2=\"20\" \n"
"\tstroke-width=\"2\" stroke=\"black\" />\n"
"\t<line x1=\"30\" y1=\"30\" x2=\"70\" y2=\"30\" \n"
"\tstroke-width=\"2\" stroke=\"black\" />\n"
"\t<line x1=\"40\" y1=\"40\" x2=\"60\" y2=\"40\" \n"
"\tstroke-width=\"2\" stroke=\"black\" />\n"
"\t<line x1=\"45\" y1=\"50\" x2=\"55\" y2=\"50\" \n"
"\tstroke-width=\"2\" stroke=\"black\" />" ;

/*Function to add a component to the graph*/

void AddComponent(char *name, char *net1, char *net2 ,float num, char *multiplier)
{
	char type;
	float nn = num;
	vertice *a, *b;
	
	/*checking whether net exists already else adding to list of nets*/
	
	if(findInAdjList(circuit->myAdjList,net1) == NULL )
	{
		a = newVertice(net1);
		adjListInsert(circuit->myAdjList, a);
	}
	else
	{
		a= findInAdjList(circuit->myAdjList,net1);
	}
	if(findInAdjList(circuit->myAdjList,net2) == NULL )
	{
		b = newVertice(net2);
		adjListInsert(circuit->myAdjList, b);
	}
	else
	{
		b = findInAdjList(circuit->myAdjList,net2);
	}

	/*Getting the numerical value */
	
	if(strcmp(multiplier,"FF") == 0 )
	{
		type = 'C';
		nn *= powf(10,-15);
	}
	else if(strcmp(multiplier,"PF") == 0 )
	{
		type = 'C';
		nn *= powf(10,-12);
	}
	else if(strcmp(multiplier,"NF") == 0 )
	{
		type = 'C';
		nn *= powf(10,-9);
	}
	else if(strcmp(multiplier,"MF") == 0 )
	{
		type = 'C';
		nn *= powf(10,-3);
	}
	else if(strcmp(multiplier,"KF") == 0 )
	{
		type = 'C';
		nn *= powf(10,3);
	}
	else if(strcmp(multiplier,"MEGF") == 0 )
	{
		type = 'C';
		nn *= powf(10,6);
	}
	else if(strcmp(multiplier,"UF") == 0 )
	{
		type = 'C';
		nn *= powf(10,-6);
	}
	else if(strcmp(multiplier,"F") == 0 )
	{
		type = 'C';
	}
	else if(strcmp(multiplier,"FH") == 0 )
	{
		type = 'L';
		nn *= powf(10,-15);
	}
	else if(strcmp(multiplier,"PH") == 0 )
	{
		type = 'L';
		nn *= powf(10,-12);
	}
	else if(strcmp(multiplier,"NH") == 0 )
	{
		type = 'L';
		nn *= powf(10,-9);
	}
	else if(strcmp(multiplier,"UH") == 0 )
	{
		type = 'L';
		nn *= powf(10,-6);
	}
	else if(strcmp(multiplier,"MH") == 0 )
	{
		type = 'L';
		nn *= powf(10,-3);

	} else if(strcmp(multiplier,"KH") == 0 )
	{
		type = 'L';
		nn *= powf(10,3);
	}
	else if(strcmp(multiplier,"MEGH") == 0 )
	{
		type = 'L';
		nn *= powf(10,6);
	}
	else if(strcmp(multiplier,"H") == 0 )
	{
		type = 'L';
	}
	else if(strcmp(multiplier,"R") == 0 )
	{
		type = 'R';
	}
	else if(strcmp(multiplier,"P") == 0 )
	{
		type = 'R';
		nn *= powf(10,-12);
	}
	else if(strcmp(multiplier,"N") == 0 )
	{
		type = 'R';
		nn *= powf(10,-9);

	}else if(strcmp(multiplier,"U") == 0 )
	{
		type = 'R';
		nn *= powf(10,-6);

	}else if(strcmp(multiplier,"M") == 0 )
	{
		type = 'R';
		nn *= powf(10,-3);

	}else if(strcmp(multiplier,"K") == 0 )
	{
		type = 'R';
		nn *= powf(10,3);

	}else if(strcmp(multiplier,"MEG") == 0 )
	{
		type = 'R';
		nn *= powf(10,6);
	}
	else
	{
		printf("One Line in Input is Wrong");
		return;
	}
	char *stu = malloc(100);
	sprintf(stu,"%g %s",num, multiplier);
	
	/*Inserting edge into edge list*/

	edge *e = newEdge(a,b,nn,name,type,stu);
	edgeListInsert(circuit->myEdgeList,e);
	edgeListInsert(e->v1->myEdgeList, e);
	edgeListInsert(e->v2->myEdgeList, e);
}

/*Function to add a source component to the graph*/

void AddSource(char *name, char *net1, char *net2, float dcOffset, float amplitude, float frequency, char* multiplier, float delay)
{
	float nn = frequency;
	vertice *a, *b;
	if(findInAdjList(circuit->myAdjList,net1) == NULL )
	{
		a = newVertice(net1);
		adjListInsert(circuit->myAdjList, a);
	}
	else
	{
		a = findInAdjList(circuit->myAdjList,net1);
	}
	if(findInAdjList(circuit->myAdjList,net2) == NULL )
	{
		b = newVertice(net2);
		adjListInsert(circuit->myAdjList, b);
	}
	else
	{
		b = findInAdjList(circuit->myAdjList,net2);
	}
	if((strcmp(multiplier,"HZ") == 0) || (strcmp(multiplier,"hz") == 0) )
	{
	}
	else if((strcmp(multiplier,"KHZ") == 0) || (strcmp(multiplier,"Khz") == 0) )
	{
		nn *= powf(10,3);
	}
	else if((strcmp(multiplier,"MEGHZ") == 0)|| strcmp(multiplier,"MEGhz") == 0 )
	{
		nn *= powf(10,6);
	}
	else if((strcmp(multiplier,"NHZ") == 0) || (strcmp(multiplier,"Nhz") == 0) )
	{
		nn *= powf(10,-9);
	}
	else if((strcmp(multiplier,"UHZ") == 0) || (strcmp(multiplier,"Uhz") == 0) )
	{
		nn *= powf(10,-6);
	}
	else if((strcmp(multiplier,"MHZ") == 0) || (strcmp(multiplier,"Mhz") == 0) )
	{
		nn *= powf(10,-3);
	}
	else if((strcmp(multiplier,"PHZ") == 0) || (strcmp(multiplier,"Phz") == 0))
	{
		nn *= powf(10,-12);
	}
	else if((strcmp(multiplier,"FHZ") == 0) || (strcmp(multiplier,"Fhz") == 0))
	{
		nn *= powf(10,-15);
	}
	else
	{
		printf("One Line in Input is Wrong");
		return;
	}

	edge *e;
	char *stu = malloc(100);
	sprintf(stu,"SINE (%g %g %g%s %gS 0) ",dcOffset,amplitude,frequency,multiplier, delay);
	if(name[0]=='V')
	{
		e = newEdge(a,b,nn,name,'V',stu);

	}
	else if(name[0] == 'I')
	{

		e = newEdge(a,b,nn,name,'I',stu);
	}
	else
	{
		printf("One Line in Input is Wrong");
		return;
	}
	e->info->isSource = 1;
	e->info->offSet = dcOffset;
	e->info->amplitude = amplitude;
	e->info->delay = delay;
	edgeListInsert(circuit->myEdgeList,e);
	edgeListInsert(e->v1->myEdgeList, e);
	edgeListInsert(e->v2->myEdgeList, e);
}

int main(int argc, char *argv[]) 
{
	/*Our graph initialisation*/
	circuit = newGraph();

	/*Reading from file*/
	if(argc==3)
	{
		yyin = fopen(argv[1], "r");
		output = fopen(argv[2],"w");
	}
	else if(argc==2)
	{
		yyin = fopen(argv[1], "r");
		output = fopen("oout.svg","w");
	}
	else
	{
		yyin = fopen("in.txt", "r");
		output = fopen("oout.svg","w");
	}

	yyparse();

	/*Writing initial part of the svg file*/

	fprintf(output,"<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"%d\" height=\"%d\"> \n ",200*circuit->myAdjList->size + 200, 200*circuit->myEdgeList->size + 200);
	int i;
	int noedges = circuit->myEdgeList->size;

	/*Drawing the grid*/

	for(i=0; i<circuit->myAdjList->size; i++)
	{
		if(strcmp(*getInAdjList(circuit->myAdjList,i)->netName,"0")==0)
		{
			fprintf(output, "\t<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"2\" stroke=\"black\" />\n ", 50 + i*200 , 25  ,150 + i*200  , 25);
			fprintf(output,"<ellipse cx=\"%d\" cy=\"%d\" rx=\"5\" ry=\"5\" stroke=\"black\" stroke-width=\"2\" fill=\"black\" /> ",150 + i*200,25);

			/*Drawing ground symbol*/

			fprintf(output,"<g transform=\"translate(%d,%d)\">\n",100 + i*200,25);
			fprintf(output,ground);
			fprintf(output,"</g>");
		}
		fprintf(output, "\t<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"2\" stroke=\"black\" />\n ", 50 + i*200 , 25  ,50 + i*200  , (noedges)*200 + 100);
		fprintf(output,"<g fill=\"#000000\" font-family=\"Arial,Helvetica\" font-weight=\"bold\" text-anchor=\"start\" font-size=\"22px\">\n<text x=\"%d\" y=\"%d\">%s</text></g>",55 + i*200,50,*getInAdjList(circuit->myAdjList,i)->netName);
		fprintf(output,"<ellipse cx=\"%d\" cy=\"%d\" rx=\"5\" ry=\"5\" stroke=\"black\" stroke-width=\"2\" fill=\"black\" /> ",50 + i*200,25);
		fprintf(output,"<ellipse cx=\"%d\" cy=\"%d\" rx=\"5\" ry=\"5\" stroke=\"black\" stroke-width=\"2\" fill=\"black\" /> ",50 + i*200 ,  (noedges)*200 + 100);
	}
	char myType;
	int start,end,ttt;
	edge *myed;

	/*Drawing the components*/

	for(i=0;i<circuit->myEdgeList->size;i++)
	{
		myed = getInEdgeList(circuit->myEdgeList,i);
		myType = myed->info->type;
		start = indexInAdjList(circuit->myAdjList,myed->v1->netName);
		end = indexInAdjList(circuit->myAdjList,myed->v2->netName);
		if(start>= end)
		{
			ttt = start;
			start = end;
			end = ttt;
		}
		fprintf(output,"<g transform=\"translate(%f,%d)\">\n",((start+end)/2.0)*200,100+200*i);
		if(myType == 'R')
		{
			fprintf(output,resistor);
		}
		if(myType == 'L')
		{
			fprintf(output,inductor);
		}
		if(myType == 'C')
		{
			fprintf(output,capacitor);
		}
		if(myType == 'V')
		{
			fprintf(output,voltageSource);
		}
		if(myType == 'I')
		{
			fprintf(output,currentSource);
		}
		fprintf(output,"</g>");

		/*Draw connecting wires*/
		fprintf(output, "\t<line x1=\"%d\" y1=\"%d\" x2=\"%f\" y2=\"%d\" stroke-width=\"2\" stroke=\"black\" />\n ", 50+start*200 ,125+200*i , ((start+end)/2.0)*200 , 125+200*i);
		fprintf(output, "\t<line x1=\"%f\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"2\" stroke=\"black\" />\n ",100+((start+end)/2.0)*200 , 125+200*i , end*200 + 50 , 125+200*i);
		fprintf(output,"<ellipse cx=\"%d\" cy=\"%d\" rx=\"5\" ry=\"5\" stroke=\"black\" stroke-width=\"2\" fill=\"black\" /> ",50+start*200,125+200*i);
		fprintf(output,"<ellipse cx=\"%d\" cy=\"%d\" rx=\"5\" ry=\"5\" stroke=\"black\" stroke-width=\"2\" fill=\"black\" /> ",end*200 + 50 , 125+200*i);
		fprintf(output,"<g fill=\"#000000\" font-family=\"Arial,Helvetica\" font-weight=\"bold\" text-anchor=\"start\" font-size=\"22px\">\n<text x=\"%d\" y=\"%d\">%s</text></g>", 60 ,117+200*i,myed->info->name);
		fprintf(output,"<g fill=\"#000000\" font-family=\"Arial,Helvetica\" font-weight=\"bold\" text-anchor=\"start\" font-size=\"22px\">\n<text x=\"%d\" y=\"%d\">%s</text></g>", 60 ,168+200*i,myed->info->stringed);
	}
	printEdgeList(circuit->myEdgeList);
	printAdjList(circuit->myAdjList);
	fprintf(output,"</svg>");
	fclose(output);
	return 0;
}