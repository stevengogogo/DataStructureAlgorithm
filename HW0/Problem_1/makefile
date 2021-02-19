CFLAGS = -I.

BUILD: 
	mkdir -p build
	gcc -o build/main main.c bigint.c 


TEST:
	mkdir -p test/build
	gcc -o test/build/test.out test/runtest.c
	./test/build/test.out


RUN:
	./build/main < test/INPUT

