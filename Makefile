build:
	rm -f chart.o main.o
	gcc -c ./charts/chart.c -o chart.o
	gcc -c main.c -o main.o
	gcc -o main chart.o main.o