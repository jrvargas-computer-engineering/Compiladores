# Grupo A - Alunos:
# Juliana Rodrigres de Vargas- 00337553
# Sofia Popsin Gomes - 00313563

CC=gcc

# nome do executavel final
TARGET = etapa5

# arquivos de objeto
OBJ = main.o parser.tab.o lex.yy.o asd.o tabela.o parser_helpers.o iloc.o 

#flags
CFLAGS = -g -Wall -Werror -fsanitize=address
all: $(TARGET)

# Dependencias explicitas (Boas praticas para garantir recompilacao)
# Se iloc.h mudar, recompila quem usa ele
main.o: main.c asd.h iloc.h
iloc.o: iloc.c iloc.h
asd.o: asd.c asd.h iloc.h

# linking
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(TARGET) 

%.o: %.c
	$(CC) $(CFLAGS) -c  $< -o $@
	
# Bison 
parser.tab.c parser.tab.h: parser.y tabela.h asd.h types.h parser_helpers.h diretivas.h iloc.h
	bison -d parser.y

#flex executado se scanner.l ou parser.tab.h foram alterados
lex.yy.c: scanner.l parser.tab.h
	flex scanner.l

clean: 
	rm -f $(TARGET) $(OBJ) .o lex.yy.c parser.tab.c parser.tab.h parser.output *.dot *.png *.tgz *.iloc *.txt

tgz: clean
	tar cvzf $(TARGET).tgz --exclude=$(TARGET).tgz .
