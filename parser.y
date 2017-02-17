%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include<string.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern FILE* yyout; 

void yyerror(const char* s);
%}

%defines
%error-verbose

%code requires
{
	void AddComponent(char *name, char *net1, char *net2 ,float num, char *multiplier);
	void AddSource(char *name, char *net1, char *net2, float dcOffset, float amplitude, float frequency, char* multiplier, float delay);
}

%union
{
	float num;
	char* id;
}

%token<num> NUMBER
%token SINE LEFT RIGHT
%token NEWLINE
%token<id> ID 

%%

line: 
	| line NEWLINE {}
	| line ID ID ID NUMBER ID NEWLINE 		{AddComponent($2,$3,$4,$5,$6);}
	| line ID ID ID SINE LEFT NUMBER NUMBER NUMBER ID NUMBER ID RIGHT NEWLINE	{AddSource($2,$3,$4,$7,$8,$9,$10,$11);}
	| line ID ID ID SINE LEFT NUMBER NUMBER NUMBER ID NUMBER ID NUMBER RIGHT NEWLINE	{AddSource($2,$3,$4,$7,$8,$9,$10,$11);}

;
%%

void AddComponent(char *name, char *net1, char *net2 ,float num, char *multiplier)
{
	/*Multiplier consists of units and power*/

	printf("%s-%s-%s\n",name,net1,net2);
}

void AddSource(char *name, char *net1, char *net2, float dcOffset, float amplitude, float frequency, char* multiplier, float delay)
{
	/*Multiplier consists of units and power*/
	printf("%s-%s-%s\n",name,net1,net2);
}

int main(int argc ,char *argv[]) 
{
	yyin = fopen(argv[1],"r");
	//yyout = fopen(argv[2],"w+");
	yyparse();
	return 0;
}

void yyerror(const char* s) 
{
	printf("SynErr:%s\n",s);
	//exit(1);
}
