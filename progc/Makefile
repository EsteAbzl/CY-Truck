# Vars
CC := gcc
override CFLAGS += -Wno-everything -lm -O2
SOURCEDIR := ./src
BINDIR := ./bin
FILES := $(shell find $(SOURCEDIR) -name '*.c')


# Default case
main:
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $(BINDIR)/cy-trucks.exe $(FILES)

# Clean jop
clean:
	rm -f $(BINDIR)/cy-trucks.exe