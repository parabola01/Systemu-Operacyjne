#ROZSZEZENIA
.SUFFIXES: .c .o .x .h

#KATALOG
DIR = `basename $(CURDIR)`

#NAZWY PLIKOW
NAME1 = main

#PROGRAMY WYKONAWCZE
EXEC1 = $(NAME1).x

#PLIKI PO KOMPILACJI
OBJS1 = $(NAME1).o

# KOMPILATOR I LINKER 
CO = gcc
LD = $(CO)

#FLAGI KOMPILATORA I LINKERA
CFLAGS = -Wall -std=c99 -pedantic -O 
LFLAGS = -Wall -std=c99 -pedantic -O

#REGULA WZORCOWA
%.o: %.c
	$(CO) $(CFLAGS) -c $<

#REGULY ZALEZNOSCI
.PHONY: all, run
all: $(EXEC1) 
$(EXEC1): $(OBJS1) 
	$(LD) -o $@ $(LFLAGS) $^  -lpthread


#URUCHAMIANIE PROGRAMU
run: $(EXEC1)
	./$(EXEC1)

#CLEANER
.PHONY: clean tar
clean: 
	rm -f *.o  *~ *.a *.so *.x core core* a.out;

#ARCHIWIZACJA I KOMPRESJA
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )