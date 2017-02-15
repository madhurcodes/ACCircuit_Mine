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

%union
{
	float num;
	char* id;
}

%token<num> NUMBER
%token SINE K M N H F LEFT RIGHT HZ S
%token NEWLINE
%token<id> RESIS INDUC CAPAC VOSRC CUSRC NETID 

%%

line: 
	| RESIS NETID NETID NUMBER K NEWLINE	{printf("%s-%s-%s-%f",$1,$2,$3,$4);}
	| RESIS NETID NETID NUMBER M NEWLINE	{printf("%s-%s-%s-%f",$1,$2,$3,$4);}
	| RESIS NETID NETID NUMBER N NEWLINE	{printf("%s-%s-%s-%f",$1,$2,$3,$4);}
	| RESIS NETID NETID NUMBER NEWLINE		{printf("%s-%s-%s-%f",$1,$2,$3,$4);}
	| CAPAC NETID NETID NUMBER K F NEWLINE	{printf("%s-%s-%s-%f",$1,$2,$3,$4);}
	| CAPAC NETID NETID NUMBER M F NEWLINE	{printf("%s-%s-%s-%f",$1,$2,$3,$4);}
	| CAPAC NETID NETID NUMBER N F NEWLINE	{printf("%s-%s-%s-%f",$1,$2,$3,$4);}
	| CAPAC NETID NETID NUMBER F NEWLINE	{printf("%s-%s-%s-%f",$1,$2,$3,$4);}
	| INDUC NETID NETID NUMBER K H NEWLINE	{printf("%s-%s-%s-%f",$1,$2,$3,$4);}
	| INDUC NETID NETID NUMBER M H NEWLINE	{printf("%s-%s-%s-%f",$1,$2,$3,$4);}
	| INDUC NETID NETID NUMBER N H NEWLINE	{printf("%s-%s-%s-%f",$1,$2,$3,$4);}
	| INDUC NETID NETID NUMBER H NEWLINE	{printf("%s-%s-%s-%f",$1,$2,$3,$4);}
	| VOSRC NETID NETID SINE LEFT NUMBER NUMBER NUMBER K HZ NUMBER S RIGHT NEWLINE	{}
	| VOSRC NETID NETID SINE LEFT NUMBER NUMBER NUMBER N HZ NUMBER S RIGHT NEWLINE	{}
	| VOSRC NETID NETID SINE LEFT NUMBER NUMBER NUMBER HZ NUMBER S RIGHT NEWLINE	{}
	| CUSRC NETID NETID SINE LEFT NUMBER NUMBER NUMBER K HZ NUMBER S RIGHT NEWLINE	{}
	| CUSRC NETID NETID SINE LEFT NUMBER NUMBER NUMBER N HZ NUMBER S RIGHT NEWLINE	{}
	| CUSRC NETID NETID SINE LEFT NUMBER NUMBER NUMBER HZ NUMBER S RIGHT NEWLINE	{}
;
%%

int main(int argc ,char *argv[]) 
{
	yyin = fopen(argv[1],"r");
	//yyout = fopen(argv[2],"w+");
	yyparse();
	return 0;
}

void yyerror(const char* s) 
{
	printf("SynErr\n");
	//exit(1);
}
