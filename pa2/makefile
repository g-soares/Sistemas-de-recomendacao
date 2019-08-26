CC = g++
CFLAGS = -O0 -Wall -std=c++17

run: compila
	./recommender content.csv ratings.csv targets.csv > submission.csv

compila: main.o input.o
	$(CC) $(CFLAGS) main.o input.o -o recommender

main.o: main.cpp input.h
	$(CC) $(CFLAGS) -c main.cpp -o main.o

input.o: input.cpp input.h
	$(CC) $(CFLAGS) -c input.cpp -o input.o

clean:
	rm *.o