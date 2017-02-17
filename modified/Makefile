all: ac

parser.tab.c parser.tab.h:	parser.y
	bison -d parser.y

lex.yy.c: scanner.l parser.tab.h
	flex scanner.l

ac: lex.yy.c parser.tab.c parser.tab.h
	gcc -o copac parser.tab.c -lm lex.yy.c

clean:
	rm copac parser.tab.c lex.yy.c parser.tab.h input.txt out.txt
