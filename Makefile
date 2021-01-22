# Makefile 
	
szachy: main.o structure.o gamerules.o front.o
	gcc -std=c11 -Wall -Wextra main.o structure.o gamerules.o front.o -o szachy -lncurses
	
main.o: main.c source/structure.h source/gamerules.h source/front.h
	gcc -std=c11 -Wall -Wextra -c main.c -o main.o
	
structure.o: source/structure.c source/structure.h source/gamerules.h
	gcc -std=c11 -Wall -Wextra -c source/structure.c -o structure.o

gamerules.o: source/gamerules.c source/structure.h source/gamerules.h
	gcc -std=c11 -Wall -Wextra -c source/gamerules.c -o gamerules.o
	
front.o: source/front.c source/structure.h source/gamerules.h source/front.h
	gcc -std=c11 -Wall -Wextra -c source/front.c -o front.o -lncurses
