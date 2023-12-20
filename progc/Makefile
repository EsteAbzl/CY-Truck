## Doing 'make' imply 'make main' and will execute the "main" section and compile all the files under the src/ folder
##       'make clean' will execute the "clean" section and remove main.exe
## It's possible to create more "section" for other .exe (e.g: render.exe, sort.exe, compute.exe)

all: main

CC = gcc
override CFLAGS += -g -Wno-everything -pthread -lm 

## Shortcut for header's and .c's directory
DIR_SRC = src/
DIR_INC = src/
SRCS = $(wildcard $(DIR_SRC)*.c)
HEADERS = $(wildcard $(DIR_INC)*.h)


main: $(SRCS) $(HEADERS)
	$(CC) -o "$@.exe" $(SRCS)	$(CFLAGS)

clean:
	rm -f main.exe