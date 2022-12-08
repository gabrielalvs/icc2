UTIL=aluno.c lista.c tabelahash.c
MAIN=main.c
BINARY=executavel

all:
	gcc -Wall -Werror -g $(UTIL) $(MAIN) -o $(BINARY) -lm

run:
	./$(BINARY)

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)
