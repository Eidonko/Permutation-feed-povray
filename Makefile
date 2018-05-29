all:	feedpovray

feedpovray:	feedpovray.o perm.o
	gcc -o feedpovray feedpovray.o perm.o

feedpovray.o:	feedpovray.c
	gcc -c feedpovray.c

perm.o:	perm.c
	gcc -c perm.c

