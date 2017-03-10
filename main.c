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
float pii = 3.141592653589793238462643383279502884197169399375105820974944592307816406286;

extern float* mmmm;
extern graph *circuit;

int rowno = 0;
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

char buttons[] = "    </g>\n    <circle cx=\"50\" cy=\"50\" r=\"42\" fill=\"white\" opacity=\"0.75\"/>\n  <path class=\"button\" onmousedown=\"pan( 0, 50)\" d=\"M50 10 l12   20 a40, 70 0 0,0 -24,  0z\" />\n  <path class=\"button\" onmousedown=\"pan( 50, 0)\" d=\"M10 50 l20  -12 a70, 40 0 0,0   0, 24z\" />\n  <path class=\"button\" onmousedown=\"pan( 0,-50)\" d=\"M50 90 l12  -20 a40, 70 0 0,1 -24,  0z\" />\n  <path class=\"button\" onmousedown=\"pan(-50, 0)\" d=\"M90 50 l-20 -12 a70, 40 0 0,1   0, 24z\" />\n  \n  <circle class=\"compass\" cx=\"50\" cy=\"50\" r=\"20\"/>\n  <circle class=\"button\"  cx=\"50\" cy=\"41\" r=\"8\" onclick=\"zoom(0.8)\"/>\n  <circle class=\"button\"  cx=\"50\" cy=\"59\" r=\"8\" onclick=\"zoom(1.25)\"/>\n\n  <rect class=\"plus-minus\" x=\"46\" y=\"39.5\" width=\"8\" height=\"3\"/>\n  <rect class=\"plus-minus\" x=\"46\" y=\"57.5\" width=\"8\" height=\"3\"/>\n  <rect class=\"plus-minus\" x=\"48.5\" y=\"55\" width=\"3\" height=\"8\"/>\n</svg>";

char scripts[]= "\n  \n  <style>\n  \t\t.territory:hover{\n\t\t\tfill:           #22aa44;\n\t\t}\n  \t\t.compass{\n  \t\t\tfill:\t\t\t#fff;\n  \t\t\tstroke:\t\t\t#000;\n  \t\t\tstroke-width:\t1.5;\n  \t\t}\n   \t\t.button{\n\t\t    fill:           \t#225EA8;\n\t\t\tstroke:   \t\t\t#0C2C84;\n\t\t\tstroke-miterlimit:\t6;\n\t\t\tstroke-linecap:\t\tround;\n\t\t}\n\t\t.button:hover{\n\t\t\tstroke-width:   \t2;\n\t\t}\n\t\t.plus-minus{\n\t\t\tfill:\t#fff;\n\t\t\tpointer-events: none;\n\t\t}\n\t\t  </style>\n  <script type=\"text/ecmascript\">\n    <![CDATA[\n    var svgNS = \"http://www.w3.org/2000/svg\";\n    var re1   = /matrix\\((\\S+) (\\S+) (\\S+) (\\S+) (\\S+) (\\S+)\\)/;\n    var re2   = /translate\\((\\S+) (\\S+)\\)/;\n\tvar trans_matrix = [1,0,0,1,0,0]\n\n    function init(evt)\n    {\n        if ( window.svgDocument == null )\n        {\n            svgDocument = evt.target.ownerDocument;\n        }\n        mapTransform = svgDocument.getElementById(\"viewport\");\n        nameTranslate = svgDocument.getElementById(\"names\");\n    }\n   \n\n    function pan(dx, dy)\n    {\n    \n\t\tvar current_transform = mapTransform.getAttributeNS(null, \"transform\");\n\t\tvar match = re1.exec(current_transform);\n     \n    \tmatch[5] = parseFloat(match[5]) + dx;\n    \tmatch[6] = parseFloat(match[6]) + dy;\n    \n    \tnew_transform = \"matrix(\" +  match.slice(1).join(' ') + \")\";\n    \tmapTransform.setAttributeNS(null, \"transform\", new_transform);\n        \n    \t/*for (var i=0; i<nameTranslate.childNodes.length; i++)\n    \t{\n    \t\tif (nameTranslate.childNodes[i].nodeName == \"text\")\n    \t\t{\n    \t\t\tvar child = nameTranslate.childNodes[i];\n    \t\t\tvar x = parseFloat(child.getAttributeNS(null, \"x\"));\n    \t\t\tvar y = parseFloat(child.getAttributeNS(null, \"y\"));\n\t\t    \tvar new_x = x + dx;\n    \t\t\tvar new_y = y + dy;\n    \t\t\tchild.setAttributeNS(null, \"x\", new_x);\n    \t\t\tchild.setAttributeNS(null, \"y\", new_y);\n    \t\t}\n    \t}*/\n    }   \n\n    function zoom(scale)\n\t{\n\t\tvar current_transform = mapTransform.getAttributeNS(null, \"transform\");\n\t\tvar match = re1.exec(current_transform);\n            \n       \tmatch[1] = parseFloat(match[1]) * scale;\n        match[2] = parseFloat(match[2]) * scale;\n    \tmatch[3] = parseFloat(match[3]) * scale;\n    \tmatch[4] = parseFloat(match[4]) * scale;\n    \tmatch[5] = parseFloat(match[5]) * scale + (1-scale)*250;\n    \tmatch[6] = parseFloat(match[6]) * scale + (1-scale)*150;\n    \n    \tnew_transform = \"matrix(\" +  match.slice(1).join(' ') + \")\";\n    \tmapTransform.setAttributeNS(null, \"transform\", new_transform);\n\n    \tfor (var i=0; i<nameTranslate.childNodes.length; i++)\n    \t{\n    \t\tif (nameTranslate.childNodes[i].nodeName == \"text\")\n    \t\t{\n    \t\t\tvar child = nameTranslate.childNodes[i];\n    \t\t\tvar x = parseFloat(child.getAttributeNS(null, \"x\"));\n    \t\t\tvar y = parseFloat(child.getAttributeNS(null, \"y\"));\n\t\t    \tvar new_x = 250 - (250 - x) * scale;\n    \t\t\tvar new_y = 150 - (150 - y) * scale;\n    \t\t\tchild.setAttributeNS(null, \"x\", new_x);\n    \t\t\tchild.setAttributeNS(null, \"y\", new_y);\n    \t\t}\n    \t}\n\n    }\n    \n  ]]></script>\n<g id=\"viewport\" transform=\"matrix(1 0 0 1 200 200)\">";







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

void assigncomplex(float w, float matrix[][2 * circuit->myAdjList->size + 2 * circuit->myEdgeList->size + 1])
{
	rowno=0;
	edge *myEdge;
	vertice *myVertex;
	int i=0,a=0;
	if(w>0)
	{
		for(i=0; i<circuit->myEdgeList->size; i++)
		{
			myEdge=getInEdgeList(circuit->myEdgeList,i);

			if(myEdge->info->isSource == 0)
			{
				if(myEdge->info->type == 'R')
				{	
					myEdge->z_imag = 0;
					myEdge->z_real = myEdge->info->val;	
				}
				else if(myEdge->info->type == 'L') 
				{	
					myEdge->z_imag = myEdge->info->val*w*2*pii;
					myEdge->z_real = 0;	
				}
				else if(myEdge->info->type == 'C') 
				{	
					myEdge->z_imag = -1/(myEdge->info->val*w*2*pii);
					myEdge->z_real = 0;
				}
				else
				{
					printf("error: wrong type");
				}
				//v1_real-v2_real-i_real*z_real+i_imag*z_imag=0
				//v1_imag-v2_imag-i_imag_z_real-i_real*z_imag=0
				//add myEdge->v1->v_real,v_imag; neg myEdge->v2->v_real,imag; myEdge->z_imag

				a= 2 * indexInAdjList(circuit->myAdjList,myEdge->v1->netName);
				matrix[rowno][a]=1;
				a= 2 * indexInAdjList(circuit->myAdjList,myEdge->v2->netName);
				matrix[rowno][a]=-1;
				a= 2 * circuit->myAdjList->size + 2*indexInEdgeList(circuit->myEdgeList,myEdge->info->name);
				matrix[rowno][a]=-1*myEdge->z_real;
				a= 2 * circuit->myAdjList->size + 2*indexInEdgeList(circuit->myEdgeList,myEdge->info->name) + 1;
				matrix[rowno][a]=myEdge->z_imag;
				rowno++;
				a= 2 * indexInAdjList(circuit->myAdjList,myEdge->v1->netName)+1;
				matrix[rowno][a]=1;
				a= 2 * indexInAdjList(circuit->myAdjList,myEdge->v2->netName)+1;
				matrix[rowno][a]=-1;
				a= 2 * circuit->myAdjList->size + 2*indexInEdgeList(circuit->myEdgeList,myEdge->info->name) + 1;
				matrix[rowno][a]=-1*myEdge->z_real;
				a= 2 * circuit->myAdjList->size + 2*indexInEdgeList(circuit->myEdgeList,myEdge->info->name);
				matrix[rowno][a]=myEdge->z_imag;
				rowno++;
			}
			else
			{
				if(myEdge->info->type == 'I')
				{
					myEdge->i_imag = 0;
					myEdge->i_real = myEdge->info->amplitude;
					a = 2 * circuit->myAdjList->size + 2*indexInEdgeList(circuit->myEdgeList,myEdge->info->name);
					matrix[rowno][a]=1;
					a = 2 * circuit->myAdjList->size + 2*circuit->myEdgeList->size;
					matrix[rowno][a]=myEdge->i_real; //see if neg
					rowno++;
					a = 2 * circuit->myAdjList->size + 2*indexInEdgeList(circuit->myEdgeList,myEdge->info->name) + 1;
					matrix[rowno][a]=1;
					// add complex here
					rowno++;
				}
				else
				{
					a= 2 * indexInAdjList(circuit->myAdjList,myEdge->v1->netName);
					matrix[rowno][a]=1;
					a= 2 * indexInAdjList(circuit->myAdjList,myEdge->v2->netName);
					matrix[rowno][a]=-1;
					a= 2 * circuit->myAdjList->size + 2 * circuit->myEdgeList->size;
					matrix[rowno][a]= - myEdge->info->amplitude; //see if neg
					rowno++;
					a= 2 * indexInAdjList(circuit->myAdjList,myEdge->v1->netName)+1;
					matrix[rowno][a]=1;
					a= 2 * indexInAdjList(circuit->myAdjList,myEdge->v2->netName)+1;
					matrix[rowno][a]=-1;
					a= 2 * circuit->myAdjList->size + 2 * circuit->myEdgeList->size;
					// add complex here

					rowno++;
				}
			}
		}
		for(i=0; i<circuit->myAdjList->size - 1; i++)
		{
			myVertex = getInAdjList(circuit->myAdjList,i);
			int j=0;
			for(j=0; j<neighboursof(myVertex); j++)  //DECLARE THIS
			{
				myEdge = edgesfrom(myVertex,j);		//DECLARE THIS	
				if(indexInAdjList(circuit->myAdjList,myVertex->netName)==indexInAdjList(circuit->myAdjList,myEdge->v1->netName))
				{
					//add myEdge->i_real , myEdge->i_imag to matrix
					a = 2 * circuit->myAdjList->size + 2*indexInEdgeList(circuit->myEdgeList,myEdge->info->name);
					matrix[rowno][a]=1;
					matrix[rowno+1][a+1]=1;
				}
				else
				{
					//add neg myEdge-> i_real ,neg myEdge-> i_imag to matrix
					a = 2 * circuit->myAdjList->size + 2*indexInEdgeList(circuit->myEdgeList,myEdge->info->name);
					matrix[rowno][a]=-1;
					matrix[rowno+1][a+1]=-1;
				}
			}
			rowno+=2;
		}
		for(i=0; i<circuit->myAdjList->size; i++) {
			if (strcmp(*getInAdjList(circuit->myAdjList, i)->netName, "0") == 0) {
				break;
			}
		}
		matrix[rowno][i*2]=1;
		matrix[rowno+1][i*2+1]=1;
	}
	else
	{
		//w=0
		//set all
	}		
}

void printmatrix(float matrix[][2 * circuit->myAdjList->size + 2 * circuit->myEdgeList->size + 1])
{
	int i,j;
	for (i=0;i < 2 * circuit->myAdjList->size + 2 * circuit->myEdgeList->size + 1;i++)
	{
		for (j=0;j < 2 * circuit->myAdjList->size + 2 * circuit->myEdgeList->size + 1;j++)
			printf("%f ",matrix[i][j]);
		printf("\n----\n");
	}
	printf("\n----------------------------------------\n");

}



int main(int argc, char *argv[])
{
	/*Our graph initialisation*/
	//invert();

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
	FILE* myResult;
	myResult = fopen("results.txt","w");
	yyparse();

    float matrix[2 * circuit->myAdjList->size + 2 * circuit->myEdgeList->size + 1][2 * circuit->myAdjList->size + 2 * circuit->myEdgeList->size + 1];
	int i=0,j=0;
	for (i=0;i < 2 * circuit->myAdjList->size + 2 * circuit->myEdgeList->size + 1;i++)
		for (j=0;j < 2 * circuit->myAdjList->size + 2 * circuit->myEdgeList->size + 1;j++)
			matrix[i][j]=0;

	/*Writing initial part of the svg file*/

	fprintf(output,"<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"%d\" height=\"%d\" onload=\"init(evt)\"> \n ",200*circuit->myAdjList->size + 200, 200*circuit->myEdgeList->size + 400);
	int flag=0;
	int noedges = circuit->myEdgeList->size;

	fprintf(output,scripts);
	/*Drawing the grid*/

	for(i=0; i<circuit->myAdjList->size; i++)
	{
		if(strcmp(*getInAdjList(circuit->myAdjList,i)->netName,"0")==0)
		{
			fprintf(output, "\t<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"2\" stroke=\"black\" />\n ", 50 + i*200 , 25  ,150 + i*200  , 25);
			fprintf(output,"<ellipse cx=\"%d\" cy=\"%d\" rx=\"5\" ry=\"5\" stroke=\"black\" stroke-width=\"2\" fill=\"black\" /> ",150 + i*200,25);
            flag = 1;
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
    if(flag==0){
        printf("\nNo ground net found\n");
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
        /* To make start the net that occurs earlier for proper drawing*/
		if(start>= end)
		{
			ttt = start;
			start = end;
			end = ttt;
		}
        /* Shows a message to user if a component is shorted (still draws it)  */
        if(start==end){
            printf("\n%s is shorted on Net %s\n",myed->info->name,*myed->v2->netName);
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
		/* Draw Points on connecting wires' beginning and end */
		fprintf(output,"<ellipse cx=\"%d\" cy=\"%d\" rx=\"5\" ry=\"5\" stroke=\"black\" stroke-width=\"2\" fill=\"black\" /> ",50+start*200,125+200*i);
		fprintf(output,"<ellipse cx=\"%d\" cy=\"%d\" rx=\"5\" ry=\"5\" stroke=\"black\" stroke-width=\"2\" fill=\"black\" /> ",end*200 + 50 , 125+200*i);
		/* Write The name of the component and it's magnitude*/
        fprintf(output,"<g fill=\"#000000\" font-family=\"Arial,Helvetica\" font-weight=\"bold\" text-anchor=\"start\" font-size=\"22px\">\n<text x=\"%d\" y=\"%d\">%s</text></g>", 60 ,117+200*i,myed->info->name);
		fprintf(output,"<g fill=\"#000000\" font-family=\"Arial,Helvetica\" font-weight=\"bold\" text-anchor=\"start\" font-size=\"22px\">\n<text x=\"%d\" y=\"%d\">%s</text></g>", 60 ,168+200*i,myed->info->stringed);
	}
	//printEdgeList(circuit->myEdgeList);
	//printAdjList(circuit->myAdjList);
	fprintf(output,buttons);
	fclose(output);


	/*AC CIRCUIT SOLVER*/

	edge* myEdge;
	float w;
	for(i=0; i<circuit->myEdgeList->size; i++)
	{
		myEdge=getInEdgeList(circuit->myEdgeList,i);
		if(myEdge->info->isSource == 1)
		{
			int nose;
			int N = 2 * circuit->myAdjList->size + 2 * circuit->myEdgeList->size;
			w = myEdge->info->val;
			assigncomplex(w,matrix);
			printmatrix(matrix);
			printf("----ssssss--------");
			float * igotthis = tryin(matrix);
			//invert(matrix);
			fprintf(myResult,"FREQ = %fKHz\n",myEdge->info->val/1000.0);
			fprintf(myResult,"VOLTAGES\n");
			int in1,in2,in33;
			float real_vol,comp_vol,real_curr,comp_curr;
			for(nose=0;nose<circuit->myEdgeList->size;nose++){
				in1 = indexInAdjList(circuit->myAdjList,getInEdgeList(circuit->myEdgeList,nose)->v1->netName);
				in2 = indexInAdjList(circuit->myAdjList,getInEdgeList(circuit->myEdgeList,nose)->v2->netName);
				real_vol= mmmm[2*in1] - mmmm[2*in2];
				comp_vol= mmmm[2*in1+1] - mmmm[2*in2+1];
				fprintf(myResult,"%s %f %f\n",getInEdgeList(circuit->myEdgeList,nose)->info->name,0.001*sqrtf(real_vol*real_vol+comp_vol*comp_vol),atanf(comp_vol/real_vol)*180/pii);
			}
			fprintf(myResult,"\n");
			fprintf(myResult,"CURRENTS\n");
			for(nose=0;nose<circuit->myEdgeList->size;nose++){
			//	in33 = indexInEdgeList(circuit->myEdgeList,getInEdgeList(circuit->myEdgeList,nose)->info->name);
				real_curr = mmmm[2 * circuit->myAdjList->size + nose*2];
				comp_curr = mmmm[2 * circuit->myAdjList->size + nose*2 + 1];
				fprintf(myResult,"%s %f %f\n",getInEdgeList(circuit->myEdgeList,nose)->info->name,sqrtf(real_curr*real_curr+comp_curr*comp_curr)/1000,atanf(comp_curr/real_curr)*180/pii);
			}
			fprintf(myResult,"\n\n");

		}
	}


	return 0;
}

