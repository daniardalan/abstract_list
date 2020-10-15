CC=gcc
CFLAGS=-I.
DEPS = list.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: abstract_list.o test_list.o
	$(CC) -o test test_list.o abstract_list.c -lm