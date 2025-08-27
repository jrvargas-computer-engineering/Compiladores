CC=gcc

OBJ = main.o lex.yy.o

.PHONY: all run

all: etapa1

etapa1: $(OBJ)
	$(CC) $^ -o etapa1

%.o: %.c
	$(CC) -c  $< -o $@

lex.yy.c: scanner.l
	flex scanner.l

run: etapa1
	cat $(TEST_FILE) | ./etapa1

clean:
	rm -f *.o lex.yy.c etapa1