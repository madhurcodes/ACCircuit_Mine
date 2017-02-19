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

extern void AddComponent(char *name, char *net1, char *net2 ,float num, char *multiplier);
extern void AddSource(char *name, char *net1, char *net2, float dcOffset, float amplitude, float frequency, char* multiplier, float delay);

void yyerror(const char* s);
%}

%defines
%error-verbose

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
	| line ID ID ID NUMBER NEWLINE 		{AddComponent($2,$3,$4,$5,"R");}
	| line ID ID ID SINE LEFT NUMBER NUMBER NUMBER ID NUMBER ID RIGHT NEWLINE	{AddSource($2,$3,$4,$7,$8,$9,$10,$11);}
	| line ID ID ID SINE LEFT NUMBER NUMBER NUMBER ID NUMBER ID NUMBER RIGHT NEWLINE	{AddSource($2,$3,$4,$7,$8,$9,$10,$11);}

;
%%

/*Writing syntax errors but continuing the program*/

void yyerror(const char* s) 
{
	printf("SynErr:%s\n",s);
	yyparse();
}
