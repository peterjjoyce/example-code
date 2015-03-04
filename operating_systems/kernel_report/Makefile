CC=gcc
CFLAGS=-I.
DEPS = fileReader.h kernelReport.h
OBJ = fileReader.o kernelReport.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

kernelReport: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
