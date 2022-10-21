 mymalloc.o: mymalloc.c mymalloc.h
	gcc -c -w mymalloc.c

main.o: main.c mymalloc.h
	gcc -c -w main.c

lib: main.o mymalloc.o
	ar rcs mymalloc.a main.o mymalloc.o

main: main.o mymalloc.a
	gcc main.o mymalloc.a -o main

remove:
	rm -rf main
	rm -rf *.o
	rm -rf *.a
