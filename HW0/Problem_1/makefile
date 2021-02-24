CFLAGS = -I.
MAKEFLAGS += --silent

.PHONY: BUILD TEST RUN  BUILD_RUN  # Main piplines
.PHONY: RUNTEST COMPILE_MAIN MERGE MERGETEST cleantest clean


build_folder = build
testbuild =  test/build
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



MERGETEST:
	mkdir -p $(testbuild)

	rsync -av --progress --quiet test $(testbuild) --exclude $(testbuild)
	rsync -av --progress --quiet $(src_folder) $(testbuild) 
	rsync -av --progress --quiet $(inc_folder) $(testbuild) 

	cp -R $(testbuild)/test/* $(testbuild)	
	cp -R $(testbuild)/$(src_folder)/* $(testbuild)	
	cp -R $(testbuild)/$(inc_folder)/* $(testbuild)
	rm $(testbuild)/main.c

COMPILE_MAIN: 
	gcc -g3 -o $(build_folder)/main.out $(build_folder)/*.c



BUILD:  MERGE COMPILE_MAIN 
	echo "$(green)Built and deploy at $(mag) $(build_folder)/$(outfile)$(reset)";



RUNTEST: MERGETEST 
	gcc -g3 -o $(testbuild)/test.out $(testbuild)/*.c
	./test/build/test.out 

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
	mkdir -p tmp_ && mv $(testbuild)/test.out tmp_  
	rm -r $(testbuild)/*
	mv tmp_/* $(testbuild) && rm -r tmp_   



