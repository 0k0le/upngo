flags = -c -Wextra -Wall
debugflags = -D_DEBUG
bindir = release

compile-debug: src/main.c src/upngo.c src/func.c
	gcc src/main.c $(flags) $(debugflags) -o bin-int/main.o
	gcc src/func.c $(flags) $(debugflags) -o bin-int/func.o
	gcc src/upngo.c $(flags) $(debugflags) -o bin-int/upngo.o

compile-release: src/main.c src/upngo.c src/func.c
	gcc src/main.c $(flags) -o bin-int/main.o
	gcc src/func.c $(flags) -o bin-int/func.o
	gcc src/upngo.c $(flags) -o bin-int/upngo.o

release: compile-release
	gcc bin-int/main.o bin-int/upngo.o bin-int/func.o -o bin/release/upngo

debug: compile-debug
	gcc bin-int/main.o bin-int/upngo.o bin-int/func.o -o bin/debug/upngo 

install:
	cp bin/release/upngo /usr/bin
	mkdir -p /opt/upngo/skeleton
	sudo cp -r etc/skelfiles/* /opt/upngo/skeleton/

clean:
	rm -f bin/release/upngo bin/debug/upngo bin-int/main.o bin-int/upngo.o bin-int/func.o
