# Compiladores
Repositório para a disciplina de Compiladores, ofertada no 7° semestre do curso de Engenharia de Computação (UFRGS).



## Etapa 1
Para montar: 
```
make
```

Para executar: 
```
make run TEST_FILE=testX.txt
```

[O que é Flex?](https://github.com/jrvargas-computer-engineering/Compiladores/blob/main/flex.md)


## Etapa 2
#### Log Mudanças
    Arquivos tokens.h foi descartado e substituido por parser.y


#### Comandos
```
# gera tabela de estados 
bison -v parser.y 


# etapas para compilacao 
bison -d parser.y
flex scanner.l //so recompila se o .h foi alterado (por no makefile)
gcc -c main.c
gcc -c parser.tab.c
gcc - lex.yy.c
gcc main.o parser.tab.o lex.yy.o -o etapa2 

```

Para testar
```
#criar um arquivo entrada.txt e ja pegar o return 
< entrada.txt ; echo $? 
```

Juntando tudo
```
bison -d parser.y; gcc -c main.c; gcc -c parser.tab.c; gcc -c lex.yy.c; gcc main.o parser.tab.o lex.yy.o -o etapa2; ./etapa2 < entrada.txt ; echo $?
```
