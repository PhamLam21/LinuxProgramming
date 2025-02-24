.PHONY: stage1 stage2 stage3 stage4 all clean

stage1: 
	gcc -E main.c -o main.i
stage2:
	gcc -S main.i -o main.S
stage3: 
	gcc -c main.S  -o main.o
stage4:
	gcc -o main main.o

all: test
	gcc -o main main.c
clean:
	rm -rf main main.i main.S main.o
