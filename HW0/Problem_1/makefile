CFLAGS = -I.
.PHONY: BUILD TEST RUN

BUILD: 
	mkdir -p build
	gcc -o build/main src/main.c src/bigint.c src/utils.c


TEST:
	mkdir -p test/build
	gcc -o test/build/test.out test/runtest.c src/bigint.c src/utils.c

	./test/build/test.out 


RUN:
	./build/main 

