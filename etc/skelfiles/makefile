flags = -c -Wextra -Wall
debugflags = -D_DEBUG

compile-debug: src/main.c src/func.c
	gcc src/main.c $(flags) $(debugflags) -o bin-int/main.o
	gcc src/func.c $(flags) $(debugflags) -o bin-int/func.o

compile-release: src/main.c src/func.c
	gcc src/main.c $(flags) -o bin-int/main.o
	gcc src/func.c $(flags) -o bin-int/func.o

release: compile-release
	gcc bin-int/main.o bin-int/func.o -o bin/release/*PRJNAME*

debug: compile-debug
	gcc bin-int/main.o bin-int/func.o -o bin/debug/*PRJNAME* 

install:
	cp bin/release/*PRJNAME* /usr/bin

clean:
	rm -f  bin/debug/*PRJNAME* bin-int/main.o bin-int/func.o
