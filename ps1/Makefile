# variables
CC=gcc
CFLAGS=-std=c11 -Wall #-Werror
LDLIBS=-lm -lcurses
OUTPUT=ps1

# targets
all: $(OUTPUT)

$(OUTPUT): main.o bmp.o playfair.o
	cppcheck --enable=performance --error-exitcode=1 *.c #,unusedFunction
	$(CC) $(CFLAGS) *.o $(LDLIBS) -o $@
main.o: main.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@
playfair.o: playfair.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@
bmp.o: bmp.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@
clean:
	rm *.o
	rm ps1
push:
	git commit
	gi push
