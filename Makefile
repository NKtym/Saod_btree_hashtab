all: app exp1 exp5 exp6

app: main.o btree.o hashtab.o
	gcc -Wall -O0 -g  -o app hashtab.o btree.o main.o
exp1: exp1.o btree.o hashtab.o
	gcc -Wall -O0 -g  -o exp1 hashtab.o btree.o exp1.o
exp5: exp5.o btree.o hashtab.o
	gcc -Wall -O0 -g  -o exp5 btree.o exp5.o
exp6: exp6.o btree.o hashtab.o
	gcc -Wall -O0 -g  -o exp6 hashtab.o exp6.o
main.o: main.c
	gcc -Wall -O0 -g  -c -o main.o main.c
btree.o: btree.c
	gcc -Wall -O0 -g  -c -o btree.o btree.c
hashtab.o: hashtab.c
	gcc -Wall -O0 -g -c -o hashtab.o hashtab.c
exp1.o: exp1.c
	gcc -Wall -O0 -g  -c -o exp1.o exp1.c
exp5.o: exp5.c
	gcc -Wall -O0 -g  -c -o exp5.o exp5.c
exp6.o: exp6.c
	gcc -Wall -O0 -g  -c -o exp6.o exp6.c

clean: 
	rm *.o
