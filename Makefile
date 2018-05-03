CC=gcc
LD=gcc

RM=rm

CFLAGS+=-Wall
CFLAGS+=-Wunused
CFLAGS+=-pedantic
CFLAGS+=-Werror
CFLAGS+=-std=c99

OBJECTS:=mymalloc.o
OBJECTS+=main.o

PROG:=prog

.PHONY: clean

all: prog

$(OBJECTS): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< 

$(PROG): $(OBJECTS)
	$(LD) -o $@ $^

clean:
	$(RM) -f *.o $(PROG)
