btasm: lex yacc src/btasm.c src/map.c toktab src/graph.c
	gcc -g3 -o btasm src/lex.yy.c src/y.tab.c src/btasm.c src/map.c src/graph.c src/compile.c -lfl -ly

yacc: src/btasm_ubi.y
	yacc -d src/btasm_ubi.y
	mv y.tab.c src
	mv y.tab.h src

lex: src/btasm_ubi.lex yacc
	lex -o src/lex.yy.c src/btasm_ubi.lex 

toktab: src/tables/toktab.h_tmpl src/tables/toktab.pl yacc
	cp src/tables/toktab.h_tmpl src/tables/toktab.h
	perl src/tables/toktab.pl

test: utils/test.pl btasm
	perl utils/test.pl

clean: Clean
	rm -rf btasm.dSYM src/y.tab.* src/tables/toktab.h src/lex.yy.c btasm 

.PHONY: test Clean

###############################
dot: graph.gv
	dotty graph.gv

