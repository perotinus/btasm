btasm: lex btasm.c map.c toktab graph.c
	gcc -g3 -lfl -o lexer lex.yy.c y.tab.c btasm.c map.c graph.c

yacc: btasm_ubi.y
	yacc -d btasm_ubi.y

lex: btasm_ubi.lex yacc
	lex btasm_ubi.lex

toktab: toktab.h_tmpl toktab.pl yacc
	cp toktab.h_tmpl toktab.h
	perl toktab.pl

###############################
dot: graph.gv
	dotty graph.gv

