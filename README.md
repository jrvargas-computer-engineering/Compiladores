# Compiladores
Repositório para a disciplina de Compiladores, ofertada no 7° semestre do curso de Engenharia de Computação (UFRGS).



# Etapa 1

## Comandos
### Para montar: 
```
make
```

### Para executar: 
```
make run TEST_FILE=testX.txt
```

[O que é Flex?](https://github.com/jrvargas-computer-engineering/Compiladores/blob/main/flex.md)


# Etapa 2
## Log Mudanças
    Arquivos tokens.h foi descartado e substituido por parser.y


## Comandos
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

### Para testar
```
#criar um arquivo entrada.txt e ja pegar o return 
< entrada.txt ; echo $? 
```

Juntando tudo
```
bison -d parser.y; gcc -c main.c; gcc -c parser.tab.c; gcc -c lex.yy.c; gcc main.o parser.tab.o lex.yy.o -o etapa2; ./etapa2 < entrada.txt ; echo $?
```

# Etapa 3

## Log de Mudanças


 ### Makefike
 -  Alterar processo de compilação para incluir `ast.c`e `ast.h`

 ### `parser.y` 
 - Configurada a %union para lidar com valores de tokens e nós da árvore.

- Adicionar ações semânticas no final das regras de produção em parser.y

    As ações são em sua maioria criação de nós e adição de filhos

    Os nós estão descritos em "Ações bison para construção da AST" na especificação da E3.


 - Adicionar nós na AST, com os labels:
    - **Função**: nome da função (identificador)
    - **Declaração de Variável com identificação**: lexema do token TK_COM
    - **Comando de Atribuição**: lexema do token TK_ATRIB 
    - **Chamada de função**: *call* + espaço + nome da função chamada
    - **Retorno**: lexema do token TK_RETURN
    - **Controle de fluxo**:    
        - **if c/ else opcional**: lexema do token TK_SE
        - **while**: lexema do token TK_ENQUANTO
    - **Expressões aritméticas**: próprios operadores unários ou binários
    - **Expressões lógicas e relacionais**: lexema correpondente 
    - **Identificadores literais**: próprio lexema. 

 ### `scanner.l`
- Modificado para que identificadores e literais carreguem informações (lexema e linha) através da yylval.


### `asd.c`/`asd.h`
- Adicionado um campo value à estrutura do nó da árvore.

- Atualizada a função de exportação para exibir o novo campo.
## Comandos
### Para testar 
```
make
./etapa3 < tests/teste_completo1.txt > saida.dot
dot saida.dot -Tpng -o arvore.png
```