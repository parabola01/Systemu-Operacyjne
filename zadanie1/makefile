.SUFFIXES: .c .o .x

NAME1 = 1a
NAME2 = 1b
NAME3 = 1c
NAME4 = 1d
NAME5 = 1e

EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x
EXEC4 = $(NAME4).x
EXEC5 = $(NAME5).x

OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o
OBJS4 = $(NAME4).o
OBJS5 = $(NAME5).o

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

$(EXEC3): $(OBJS3)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC4): $(OBJS4)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC5): $(OBJS5)
	$(LD) -o $@ $(LFLAGS) $^


.PHONY: run1, run2, run3, run4, run5

run1: $(EXEC1)
	./$(EXEC1)
run2: $(EXEC2)
	./$(EXEC2)
run3: $(EXEC3)
	./$(EXEC3)
run4: $(EXEC4)
	./$(EXEC4)
run5: $(EXEC5)
	./$(EXEC5)

.PHONY: clean
clean:
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR} 




