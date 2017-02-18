%option noyywrap

%{
#include <stdio.h>
#include <string.h>
#include "parser.tab.h"
int temp=0;

%}

letter    [A-Za-z]
alphanum  [A-Za-z0-9]
eve  [^ \t\n]

%%

[ \t]	;
\n						{temp = 0;return NEWLINE;}
"SINE"					{return SINE;}
"("						{return LEFT;}
")"						{return RIGHT;}
[0-9]+(\.)?[0-9]* 		{if(temp<3) { yylval.id = strdup(yytext);temp = 3;return ID;} else {yylval.num = atof(yytext);temp = 3;return NUMBER;}}
({eve})+				{yylval.id = strdup(yytext);temp++;return ID;}
%%
