CFLAGS = -I.
MAKEFLAGS += --silent

.PHONY: BUILD TEST RUN  MERGE clean COMPILE BUILD_RUN


build_folder = build
src_folder = src
inc_folder = include
outfile_name = main.out
outfile = $(build_folder)/$(outfile_name)

green=`tput setaf 2; tput bold`
mag = `tput setaf 5; `
reset=`tput sgr0`

MERGE:
	mkdir -p $(build_folder)
	cp -R $(src_folder)/* $(build_folder)	
	cp -R $(inc_folder)/* $(build_folder)

COMPILE: 
	gcc -o $(build_folder)/main.out $(build_folder)/*.c


BUILD: MERGE COMPILE clean
	echo "$(green)Built and deploy at $(mag) $(build_folder)/$(outfile)$(reset)";

TEST:
	mkdir -p test/build
	gcc -o test/build/test.out test/runtest.c src/bigint.c src/utils.c

	./test/build/test.out 


RUN:

	echo "$(green)Run $(mag) $(outfile)$(reset)"
	./$(outfile)
	

BUILD_RUN: BUILD RUN

clean: 
	@ mkdir -p tmp_ && mv $(outfile) tmp_  
	@ rm  $(build_folder)/*
	@ mv tmp_/* $(build_folder) && rm -r tmp_   

