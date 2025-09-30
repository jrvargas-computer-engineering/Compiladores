# Grupo A - Alunos:
# Juliana Rodrigres de Vargas- 00337553
# Sofia Popsin Gomes - 00313563
CC=gcc
CFLAGS=-Wall -Werror -fsanitize=address

# nome do executavel final
TARGET = etapa3

# arquivos de objeto
OBJ = main.o parser.tab.o lex.yy.o

# diretorio com testes
TEST_DIR = tests

all: $(TARGET)


# linking
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(TARGET) 

%.o: %.c
	$(CC) $(CFLAGS) -c  $< -o $@
	

# Bison 
parser.tab.c parser.tab.h: parser.y
	bison -v parser.y

#flex executado se scanner.l ou parser.tab.h foram alterados
lex.yy.c: scanner.l parser.tab.h
	flex scanner.l



test: $(TARGET)
	@for f in $(TEST_DIR)/*.txt; do \
			echo "--- Executando teste com a entrada: $$f ---"; \
			./$(TARGET) < $$f; \
			echo "--- [Código de Saída: $$?] ---"; \
			echo ""; \
		done

#exec: 
#	./etapa3 < test.txt ; echo $?


clean: 
	rm -f $(TARGET) *.o

tgz:
	tar -czvf etapa3.tgz * .??* --exclude=etapa3.tgz --exclude=.git --exclude=.vscode --exclude=__pycache__ --exclude=*.o --exclude=etapa3