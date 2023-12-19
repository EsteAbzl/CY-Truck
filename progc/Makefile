all: main

CC = gcc
override CFLAGS += -g -Wno-everything -pthread -lm 

##shortcut for header's and .c's directory
DIR_SRC = src/
DIR_INC = src/
SRCS = $(wildcard $(DIR_SRC)*.c)
HEADERS = $(wildcard $(DIR_INC)*.h)


main: $(SRCS) $(HEADERS)
	$(CC) -o "$@.exe" $(SRCS)	$(CFLAGS)

clean:
	rm -f main.exe