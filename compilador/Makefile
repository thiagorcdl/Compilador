$DEPURA=1

compilador: lex.yy.c y.tab.c compilador.o compilador.h
	gcc lex.yy.c compilador.tab.c compilador.o pilhas.c -o compilador -ly -lc

lex.yy.c: compilador.l compilador.h
	flex compilador.l

y.tab.c: compilador.y compilador.h
	bison compilador.y -d -v

compilador.o : compilador.h compiladorF.c
	gcc -c compiladorF.c -o compilador.o

mepa: MEPA
	gcc mepa.s -m32 -o mepa

MEPA:

clean : 
	rm -f compilador.tab.* lex.yy.c *~ *.o mepa compilador *.output
