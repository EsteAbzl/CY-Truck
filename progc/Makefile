# Vars
CC := gcc
override CFLAGS += -Wno-everything -lm
SOURCEDIR := ./src
BINDIR := ./bin
FILES := $(shell find $(SOURCEDIR) -name '*.c')


# Default case
main:
	@echo === Starting compile job... ===
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $(BINDIR)/cy-trucks.exe $(FILES)
	@echo === Done ! ===

# Clean jop
clean:
	rm -f $(BINDIR)/cy-trucks.exe