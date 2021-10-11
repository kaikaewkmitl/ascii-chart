build:
	rm -f histogram.o main.o
	gcc -c ./charts/histogram.c -o histogram.o
	gcc -c main.c -o main.o
	gcc -o main histogram.o main.o