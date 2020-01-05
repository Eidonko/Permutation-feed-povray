OBJECT_CLASS=-DBOXES
OBJECT_CLASS=
OBJECT_CLASS=-DBOTH
all:	feedpovray

feedpovray:	feedpovray.o perm.o
	gcc -o feedpovray feedpovray.o perm.o

feedpovray.o:	feedpovray.c
	gcc $(OBJECT_CLASS) -c feedpovray.c

perm.o:	perm.c
	gcc -c perm.c

