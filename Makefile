# Makefile
# Řešení IJC-DU2 18.4.2024
# Autor: Tadeáš Horák, FIT
# Přeloženo: gcc 11.4.0
CC=gcc
CFLAGS=-g -std=c11 -pedantic -Wall -Wextra
LDFLAGS=-g -std=c11 -pedantic -Wall -Wextra

all: tail

tail: tail.c
	$(CC) $(LDFLAGS) -o $@ $^ -lm

# Linking
#$(EXEC): $(OBJS)
#	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

# Clean target
.PHONY: clean
clean:
	rm -f *.o
	rm -f *.out
	rm -f tail

.PHONY: zip
zip: all
	zip xhorakt00.zip *.c *.h Makefile
	make clean