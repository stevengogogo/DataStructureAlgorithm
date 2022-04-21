main: main.c api.h
	gcc main.c -o main -O3 -std=c11 -w

validator/validator: validator/validator.cpp
	sudo g++ validator/validator.cpp -o validator/validator -O3

.PHONY=run
run: main validator/validator
	sudo  ./main < testdata/test.in | validator/validator
