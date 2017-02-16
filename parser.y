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
	void AddComponent(char *name, char *net1, char *net2 ,float num, char multiplier);
	void AddSource(char *name, char *net1, char *net2, float dcOffset, float amplitude, float frequency, char multiplier, float delay);
}

%union
{
	float num;
	char* id;
}

%token<num> NUMBER
%token SINE K M N H F LEFT RIGHT HZ S
%token NEWLINE
%token<id> RESIS INDUC CAPAC VOSRC CUSRC NETID 
%token serious

%%

line: 
	| line NEWLINE {}
	| line RESIS NETID NETID NUMBER K NEWLINE 	{AddComponent($2,$3,$4,$5,'K');}
	| line RESIS NETID NETID NUMBER M NEWLINE 	{AddComponent($2,$3,$4,$5,'M');}
	| line RESIS NETID NETID NUMBER N NEWLINE 	{AddComponent($2,$3,$4,$5,'N');}
	| line RESIS NETID NETID NUMBER NEWLINE 	{AddComponent($2,$3,$4,$5,'U');}
	| line CAPAC NETID NETID NUMBER K F NEWLINE {AddComponent($2,$3,$4,$5,'K');}
	| line CAPAC NETID NETID NUMBER M F NEWLINE {AddComponent($2,$3,$4,$5,'M');}
	| line CAPAC NETID NETID NUMBER N F NEWLINE {AddComponent($2,$3,$4,$5,'N');}
	| line CAPAC NETID NETID NUMBER F NEWLINE 	{AddComponent($2,$3,$4,$5,'U');}
	| line INDUC NETID NETID NUMBER K H NEWLINE {AddComponent($2,$3,$4,$5,'K');}
	| line INDUC NETID NETID NUMBER M H NEWLINE {AddComponent($2,$3,$4,$5,'M');}
	| line INDUC NETID NETID NUMBER N H NEWLINE {AddComponent($2,$3,$4,$5,'N');}
	| line INDUC NETID NETID NUMBER H NEWLINE 	{AddComponent($2,$3,$4,$5,'U');}
	| line VOSRC NETID NETID SINE LEFT NUMBER NUMBER NUMBER K HZ NUMBER S RIGHT NEWLINE	{AddSource($2,$3,$4,$7,$8,$9,'K',$12);}
	| line VOSRC NETID NETID SINE LEFT NUMBER NUMBER NUMBER M HZ NUMBER S RIGHT NEWLINE	{AddSource($2,$3,$4,$7,$8,$9,'M',$12);}
	| line VOSRC NETID NETID SINE LEFT NUMBER NUMBER NUMBER N HZ NUMBER S RIGHT NEWLINE	{AddSource($2,$3,$4,$7,$8,$9,'N',$12);}	
	| line VOSRC NETID NETID SINE LEFT NUMBER NUMBER NUMBER HZ NUMBER S RIGHT NEWLINE {AddSource($2,$3,$4,$7,$8,$9,'U',$11);}
	| line CUSRC NETID NETID SINE LEFT NUMBER NUMBER NUMBER K HZ NUMBER S RIGHT NEWLINE	{AddSource($2,$3,$4,$7,$8,$9,'K',$12);}
	| line CUSRC NETID NETID SINE LEFT NUMBER NUMBER NUMBER M HZ NUMBER S RIGHT NEWLINE	{AddSource($2,$3,$4,$7,$8,$9,'M',$12);}	
	| line CUSRC NETID NETID SINE LEFT NUMBER NUMBER NUMBER N HZ NUMBER S RIGHT NEWLINE	{AddSource($2,$3,$4,$7,$8,$9,'N',$12);}
	| line CUSRC NETID NETID SINE LEFT NUMBER NUMBER NUMBER HZ NUMBER S RIGHT NEWLINE {AddSource($2,$3,$4,$7,$8,$9,'U',$11);}
;
%%

void AddComponent(char *name, char *net1, char *net2 ,float num, char multiplier)
{
	
}

void AddSource(char *name, char *net1, char *net2, float dcOffset, float amplitude, float frequency, char multiplier, float delay)
{
	
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
