CC=gcc

# nome do executavel final
TARGET = etapa2

# arquivos de objeto
OBJ = main.o parser.tab.o lex.yy.o

# diretorio com testes
TEST_DIR = tests

all: $(TARGET)


# linking
$(TARGET): $(OBJ)
	$(CC) $^ -o $(TARGET) 

%.o: %.c
	$(CC) -c  $< -o $@
	

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
#	./etapa2 < test.txt ; echo $?


clean: 
	rm -f $(TARGET) $(OBJ) lex.yy.c parser.tab.c parser.tab.h
