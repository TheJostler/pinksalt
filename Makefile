CFLAGS = -O3 -Wextra -Wpedantic

pinksalt: sha-256.o pinksalt.c

sha-256.o: sha-256.h sha-256.c

.PHONY: all
all: pinksalt
	./pinksalt

.PHONY: clean
clean:
	rm -f pinksalt *.o
