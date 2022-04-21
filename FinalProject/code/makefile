CFLAGS = -I.
MAKEFLAGS += --silent
CCg=gcc -g -std=c11
CC= gcc  -std=c11
CCgf= gcc -pg -std=c11
CCm = quom

.PHONY: build test run_main  build_run  # Main piplines
.PHONY: runtest  mergetest cleantest clean

testenv = test/testEnv
build_folder = build
testbuild =  test/build
src_folder = src
outfile_name = main.out
outfile = $(build_folder)/$(outfile_name)

green=`tput setaf 2; tput bold`
mag = `tput setaf 5; `
reset=`tput sgr0`


# Build
build: 
	mkdir -p  $(build_folder)
	$(CCg) -o $(build_folder)/main.out $(src_folder)/*.c
	echo "$(green)Built and deploy at $(mag) $(outfile)$(reset)";

buildc:
	mkdir -p  $(build_folder)
	$(CC) -o $(build_folder)/main.out $(src_folder)/*.c
	echo "$(green)Built and deploy at $(mag) $(outfile)$(reset)";

# Test
mergetest:
	mkdir -p test_TEMP 
	mkdir -p $(testbuild) 
	cp -R src/* test_TEMP 
	cp -R test/* test_TEMP
	rm test_TEMP/main.c


runtest: mergetest 
	gcc -g3 -o $(testbuild)/test.out test_TEMP/*.c
	./$(testbuild)/test.out 

test: mergetest runtest cleantest


# Run
run_main:
	echo "$(green)Run $(mag) $(outfile)$(reset)"
	./$(outfile)
	

build_run: build run_main

# Clean
clean: 
	mkdir -p tmp_ && mv $(outfile) tmp_  
	rm -r $(build_folder)/*
	mv tmp_/* $(build_folder) && rm -r tmp_   

cleantest:
	rm -r test_TEMP

# For submission
merge_main: merge_standalone
	echo "[Start merging]"
	mkdir -p  $(build_folder)
	mkdir -p merge_temp
	cp -R src/* merge_temp
	python3 merge.py ./merge_temp/ remove_api
	$(CCm) ./merge_temp/main.c  ./merge_temp/main_merged.c
	python3 merge.py ./merge_temp/main_merged.c add_api

	gcc -o ./build/merge_main.o ./merge_temp/main_merged.c ./src/api.c
	echo "Compile Merged Main";
	echo "$(green)[Pass]$(reset)";

	
	cp ./merge_temp/main_merged.c ./build/main.c
	echo "Deployed at $(mag)./build/main.c$(reset)"

	rm -r merge_temp
	echo "$(green)[Merge success]$(reset)"

# For testing compilation: Standalone (STD)
merge_standalone:
	mkdir -p  $(build_folder)
	$(CCm) $(src_folder)/main.c  build/mainSTD.c
	$(CC) -o build/main.out build/mainSTD.c


# Memory check
leak: build
	valgrind  $(outfile) < ./test/data/test.in
	
leaktest: test 
	valgrind --leak-check=full test/build/test.out

# From DSA Template
score: merge_main 
	cp ./build/main.c $(testenv)/main.c
	make -C test/testEnv run 

buildgf: 
	mkdir -p  $(build_folder)
	$(CCgf) -o $(build_folder)/main_gprof.out $(src_folder)/*.c
	echo "$(green)Built and deploy at $(mag) $(build_folder)/main_gprof.out$(reset)";
gprof: buildgf
	$(build_folder)/main_gprof.out < test/data/test.in
	gprof $(build_folder)/main_gprof.out 
	rm gmon.out
	
