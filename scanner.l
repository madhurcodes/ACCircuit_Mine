%option noyywrap

%{
#include <stdio.h>
#include <string.h>
#include "parser.tab.h"
int temp=0;

%}

letter    [A-Za-z]
alphanum  [A-Za-z0-9]

%%

[ \t]	;
\n						{temp = 0;return NEWLINE;}
"R"({alphanum})+		{printf("res");temp =1 ;yylval.id = strdup(yytext);return RESIS;}
"L"({alphanum})+		{temp =1 ;yylval.id = strdup(yytext);return INDUC;}
"C"({alphanum})+		{temp =1 ;yylval.id = strdup(yytext);return CAPAC;}
"V"({alphanum})+		{temp =1 ;yylval.id = strdup(yytext);return VOSRC;}
"I"({alphanum})+		{temp =1 ;yylval.id = strdup(yytext);return CUSRC;}
"SINE"					{return SINE;}
[0-9]+(\.)?[0-9]* 		{if(temp ==1 || temp == 2) {temp = 0; yylval.id = strdup(yytext);return NETID;} else {yylval.num = atof(yytext);return NUMBER;}}
(Net|NET)[0-9]*			{printf("net");if(temp ==1){ temp = 2; }else {temp = 0; }yylval.id = strdup(yytext); return NETID;}
"("						{return LEFT;}
")"						{return RIGHT;}
"K"						{return K;}
"M"						{return M;}
"N"						{return N;}
"F"						{return F;}
"H"						{return H;}
"hz"					{return HZ;}
"S"						{return S;}
%%
