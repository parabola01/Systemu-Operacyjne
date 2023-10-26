.SUFFIXES: .c .o .x
DIR = `basename $(CURDIR)`

NAME1 = zadanie4

EXEC1 = $(NAME1).x

OBJS1 = $(NAME1).o

CFLAGS := -Wall -std=c99 -pedantic -O -fPIC
LFLAGS = -Wall -std=c99 -pedantic -O

CO = gcc
LD = $(CO)

%.o: %.c
	$(CO) $(CFLAGS) -c $<

.PHONY: all
all: $(EXEC1)

$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: run

run: $(EXEC1)


.PHONY: clean diff

diff:
	diff -s tekst1 tekst2
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}