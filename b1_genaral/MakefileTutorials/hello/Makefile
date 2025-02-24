
.PHONY: hello hellomake

CC := gcc
CFLAGS := -I.

INC_FILES := hello.h


%.o: %.c $(INC_FILES)
	$(CC) -c -o $@ $<

test: hello.h hello.c
	@echo $@
	@echo $<
	@echo $^

hellomake: main.o hello.o
	$(CC) -o $@ $^ $(CFLAGS)
# kiếm tra xem có 2 file .o chưa nếu chưa có thì make ra nó(rule ẩn)


hello: 
	gcc -o hello main.c hello.c -I.


clean: 
	rm -rf hello hellomake *.o
