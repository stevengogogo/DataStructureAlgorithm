CFLAGS = -I.

main: 
	gcc -o build/main main.c bigint.c 
	
run:
	./build/main < test/INPUT

test:
	./test/make-tests.sh > test/runtest.c