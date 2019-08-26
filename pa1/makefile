CC = g++
CFLAGS = -O0 -Wall -std=c++17

run: compila
	./recommender ratings.csv targets.csv > submission.csv

compila: main.o input.o alocacao.o funcoes.o
	$(CC) $(CFLAGS) main.o input.o alocacao.o funcoes.o -o recommender

main.o: main.cpp input.h alocacao.h funcoes.h
	$(CC) $(CFLAGS) -c main.cpp -o main.o

input.o: input.cpp input.h
	$(CC) $(CFLAGS) -c input.cpp -o input.o

alocacao.o: alocacao.cpp alocacao.h
	$(CC) $(CFLAGS) -c alocacao.cpp -o alocacao.o

funcoes.o: funcoes.cpp funcoes.h estruturas.h
	$(CC) $(CFLAGS) -c funcoes.cpp -o funcoes.o

clean:
	rm *.o