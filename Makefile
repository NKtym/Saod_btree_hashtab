all: app

app: main.o btree.o hashtab.o
	gcc -Wall -O0 -g  -o app hashtab.o btree.o main.o
main.o: main.c
	gcc -Wall -O0 -g  -c -o main.o main.c
btree.o: btree.c
	gcc -Wall -O0 -g  -c -o btree.o btree.c
hashtab.o: hashtab.c
	gcc -Wall -O0 -g -c -o hashtab.o hashtab.c

clean: 
	rm *.o