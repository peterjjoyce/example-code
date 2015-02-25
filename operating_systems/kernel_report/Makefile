CC=gcc
CFLAGS=-I.
DEPS = kernelReport.h
OBJ = kernelReport.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

kernelReport: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
