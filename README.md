# Compiladores-
Repositório para a disciplina de Compiladores, ofertada no 7° semestre do curso de Engenharia de Computação (UFRGS).


Para executar: 
```
flex scanner.l
gcc lex.yy.c -c; gcc main.c -c ; gcc main.o lex.yy.o -o el; cat arquivo_de_teste.txt | ./el
```