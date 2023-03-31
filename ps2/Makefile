# variables
CC=gcc
CFLAGS=-std=c11 -Wall #-Werror
LDLIBS=-lm -lcurses
OUTPUT=ps2

# targets
all: $(OUTPUT)

$(OUTPUT): main.o k.o hof.o ui.o
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c #,unusedFunction
	$(CC) $(CFLAGS) *.o $(LDLIBS) -o $@
main.o: main.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@
k.o: k.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@
hof.o: hof.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@
ui.o: ui.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@
clean:
	rm *.o
	rm ps2
