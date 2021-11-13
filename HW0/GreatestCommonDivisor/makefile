CFLAGS = -I.
MAKEFLAGS += --silent
CC=gcc -g 

.PHONY: BUILD TEST RUN  BUILD_RUN  # Main piplines
.PHONY: RUNTEST  MERGETEST cleantest clean


build_folder = build
testbuild =  test/build
src_folder = src
outfile_name = main.out
outfile = $(build_folder)/$(outfile_name)

green=`tput setaf 2; tput bold`
mag = `tput setaf 5; `
reset=`tput sgr0`



BUILD: 
	mkdir -p  $(build_folder)
	$(CC) -o $(build_folder)/main.out $(src_folder)/*.c
	echo "$(green)Built and deploy at $(mag) $(build_folder)/$(outfile)$(reset)";

MERGETEST:
	mkdir -p test_TEMP 
	mkdir -p $(testbuild) 
	cp -R src/* test_TEMP 
	cp -R test/* test_TEMP
	rm test_TEMP/main.c


RUNTEST: MERGETEST  
	gcc -g3 -o $(testbuild)/test.out test_TEMP/*.c
	./$(testbuild)/test.out 

TEST: MERGETEST RUNTEST cleantest


RUN:
	echo "$(green)Run $(mag) $(outfile)$(reset)"
	./$(outfile)
	

BUILD_RUN: BUILD RUN

clean: 
	mkdir -p tmp_ && mv $(outfile) tmp_  
	rm -r $(build_folder)/*
	mv tmp_/* $(build_folder) && rm -r tmp_   

cleantest:
	rm -r test_TEMP



