btasm: lex btasm.c map.c toktab graph.c
	gcc -g3 -o lexer lex.yy.c y.tab.c btasm.c map.c graph.c compile.c -lfl -ly

yacc: btasm_ubi.y
	yacc -d btasm_ubi.y

lex: btasm_ubi.lex yacc
	lex btasm_ubi.lex

toktab: toktab.h_tmpl toktab.pl yacc
	cp toktab.h_tmpl toktab.h
	perl toktab.pl

test: test.pl btasm
	perl test.pl

.PHONY: test

###############################
dot: graph.gv
	dotty graph.gv

