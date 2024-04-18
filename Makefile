# Makefile
# Řešení IJC-DU2 18.4.2024
# Autor: Tadeáš Horák, FIT
# Přeloženo: gcc 11.4.0
CC=gcc
CFLAGS=-g -std=c11 -pedantic -Wall -Wextra
LDFLAGS=-g -std=c11 -pedantic -Wall -Wextra

OBJLIB=htab_hash_function.o htab_init.o htab_size.o htab_bucket_count.o htab_find.o htab_lookup_add.o htab_erase.o htab_for_each.o htab_clear.o htab_free.o htab_statistics.o


all: tail wordcount wordcount-dynamic

tail: tail.c
	$(CC) $(LDFLAGS) -o $@ $^ -lm

wordcount: wordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) -o wordcount wordcount.o io.o -L . libhtab.a
	
wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) -o wordcount-dynamic wordcount.o io.o libhtab.so
	
# Staticka a dynamicka knihovna
libhtab.a: $(OBJLIB)
	ar -rcs libhtab.a $(OBJLIB)
	
libhtab.so:	$(OBJLIB)
	$(CC) $(CFLAGS) -shared -fPIC -o libhtab.so $(OBJLIB)

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