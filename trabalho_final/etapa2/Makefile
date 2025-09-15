# CC=gcc

# OBJ = main.o lex.yy.o

# .PHONY: all run

# all: etapa1

# etapa1: $(OBJ)
# 	$(CC) $^ -o etapa1

# %.o: %.c
# 	$(CC) -c  $< -o $@

# lex.yy.c: scanner.l
# 	flex scanner.l

# run: etapa1
# 	cat $(TEST_FILE) | ./etapa1

# clean:
# 	rm -f *.o lex.yy.c etapa1

CC=gcc

OBJ = main.o parser.tab.o lex.yy.o

all: etapa2

etapa2: $(OBJ)
	$(CC) $^ -o etapa2 

%.o: %.c
	$(CC) -c  $< -o $@
	
lex.yy.c: scanner.l
	flex scanner.l

parser.tab.c: parser.y
	bison -d parser.y
	bison -v parser.y

run: 
	./etapa2 < $(TEST_FILE) ; echo $?

# run em todos os arquivos da pasta tests
run_all:
	for file in test/*.txt; do \
		echo "Running test: $$file"; \
		./etapa2 < $$file ; \
		echo ""; \
	done