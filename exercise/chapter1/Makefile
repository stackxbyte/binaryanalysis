CC=gcc
OBJ=code
.PHONY: all clean

all: $(OBJ)

code: code.c
	$(CC) -S -masm=intel code.c
	$(CC) -c  code.c
	$(CC)  code.c
	cp a.out a.out.stripped
	strip --strip-all a.out.stripped

clean:
	rm -f *.s *.o a.out a.out.stripped

