C=gcc
CFLAGS=-I. -g
DEPS = header.h file_utilities.h
OBJ = main.o life.o file_utilities.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

a.out: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm a.out main.o life.o file_utilities.o
