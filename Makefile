# Makefile
# Řešení IJC-DU2 18.4.2024
# Autor: Tadeáš Horák, FIT
# Přeloženo: gcc 11.4.0
CC=gcc
CFLAGS=-g -std=c11 -pedantic -Wall -Wextra
LDFLAGS=-g -std=c11 -pedantic -Wall -Wextra

OBJLIB=htab_hash_function.o htab_init.o htab_size.o htab_bucket_count.o htab_find.o htab_lookup_add.o htab_erase.o htab_for_each.o htab_clear.o htab_free.o htab_statistics.o


all: tail wordcount wordcount-dynamic

tail: tail.o
	$(CC) $(LDFLAGS) -o $@ $^

tail.o: tail.c
	$(CC) $(CFLAGS) -o $@ -c $^



wordcount: wordcount.o io.o libhtab.a
	$(CC) $(LDFLAGS) -static -o wordcount wordcount.o io.o -L. libhtab.a
	
wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(LDFLAGS) -o wordcount-dynamic wordcount.o io.o -L. libhtab.so


wordcount.o: wordcount.c
	$(CC) $(CFLAGS) -o $@ -c $^

io.o: io.c
	$(CC) $(CFLAGS) -o $@ -c $^


htab_bucket_count.o: htab_bucket_count.c
	$(CC) $(CFLAGS) -fPIC -c $^
htab_clear.o: htab_clear.c
	$(CC) $(CFLAGS) -fPIC -c $^
htab_erase.o: htab_erase.c
	$(CC) $(CFLAGS) -fPIC -c $^
htab_find.o: htab_find.c
	$(CC) $(CFLAGS) -fPIC -c $^
htab_for_each.o: htab_for_each.c
	$(CC) $(CFLAGS) -fPIC -c $^
htab_free.o: htab_free.c
	$(CC) $(CFLAGS) -fPIC -c $^
htab_hash_function.o: htab_hash_function.c
	$(CC) $(CFLAGS) -fPIC -c $^
htab_init.o: htab_init.c
	$(CC) $(CFLAGS) -fPIC -c $^
htab_lookup_add.o: htab_lookup_add.c
	$(CC) $(CFLAGS) -fPIC -c $^
htab_size.o: htab_size.c
	$(CC) $(CFLAGS) -fPIC -c $^
htab_statistics.o: htab_statistics.c
	$(CC) $(CFLAGS) -fPIC -c $^

# Static library
libhtab.a: $(OBJLIB)
	ar -rcs -o $@ $(OBJLIB)

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
	zip xhorakt00.zip *.c *.cc *.h Makefile
	make clean

.PHONY: run
run: all
	./tail
	./wordcount
	LD_LIBRARY_PATH="." ./wordcount-dynamic
	make clean