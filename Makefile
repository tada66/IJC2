# Makefile
# Řešení IJC-DU2 18.4.2024
# Autor: Tadeáš Horák, FIT
# Přeloženo: gcc 11.4.0
CC=gcc
CFLAGS=-g -fPIC -std=c11 -pedantic -Wall -Wextra
LDFLAGS=-g -std=c11 -pedantic -Wall -Wextra

OBJLIB=htab_hash_function.o htab_init.o htab_size.o htab_bucket_count.o htab_find.o htab_lookup_add.o htab_erase.o htab_for_each.o htab_clear.o htab_free.o htab_statistics.o


all: tail wordcount wordcount-dynamic

tail: tail.o
	$(CC) $(CFLAGS) -o $@ $^

tail.o: tail.c
	$(CC) $(LDFLAGS) -o $@ -c $^



wordcount: wordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) -static -o $@ $^
	
wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) -o $@ $^


wordcount.o: wordcount.c
	$(CC) $(LDFLAGS) -o $@ -c $^

io.o: io.c
	$(CC) $(LDFLAGS) -o $@ -c $^
	

# Static library
libhtab.a: $(OBJLIB)
	ar rcs -o $@ $(OBJLIB)

# Dynamic library
libhtab.so: $(OBJLIB)
	$(CC) $(CFLAGS) -shared -o $@ $(OBJLIB)


.PHONY: cleanall
cleanall:
	rm -f *.o
	rm -f *.out
	rm -f tail
	rm -f wordcount
	rm -f wordcount-dynamic
	rm -f libhtab.a
	rm -f libhtab.so

# Clean target
.PHONY: clean
clean:
	rm -f *.o

.PHONY: zip
zip: all
	zip xhorakt00.zip *.c *.h Makefile
	make clean