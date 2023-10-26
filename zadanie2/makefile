.SUFFIXES: .c .o .x

NAME1 = 2a
NAME2 = 2b

EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x

OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o

CFLAGS := -Wall -std=c99 -pedantic -O -fPIC
LFLAGS = -Wall -std=c99 -pedantic -O

CO = gcc
LD = $(CO)

%.o: %.c
	$(CO) $(CFLAGS) -c $<

$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: run

run: $(EXEC1) $(EXEC2)
	./$(EXEC1) $(EXEC2)

.PHONY: clean
clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR} 