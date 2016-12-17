CC=g++

all: q1

q1: main.o
	$(CC) -o $@ $^
	rm -rf *.o *~

main.o: YUV2ARGB.h

.PHONY: clean

clean:
	rm -rf q1 *.o *~
