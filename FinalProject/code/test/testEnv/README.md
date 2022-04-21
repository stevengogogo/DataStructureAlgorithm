## This is the test environment for the DSA Final Project

The testdata was generated with the 10000 mails.
There are 10000 queries for you to check your implementations before submitting your code to the DSA Judge.

### Usage (for LINUX/MAC)

1. replace main.c by your own solution
2. run command "make run" to get your score of these 10000 queries

### Usage (for Windows)

1. replace main.c by your own solution
2. open your terminal (cmd or powershell) in this directory and run the commands below to compile the source codes
    - `gcc main.c -o main -O3 -std=c11 -w`
    - `g++ validator/validator.cpp -o validator/validator -O3`
3. run the command `main < testdata\test.in | validator\validator` under cmd, or `cmd.exe /c "main < testdata/test.in | validator\validator"` under powershell to get your score

### Notes and Hints

- You'll need gcc and g++ to compile the main.c and validator.cpp
- For Windows user, you may need to put your gcc/g++ compiler path into the "PATH" environment variable to run compilations successfully, also, you are highly suggested to work on CSIE workstations or WSL (Windows Subsystem for Linux), which are linux platforms
- Printing to standard error is a good way to debug.
- If you found your operating system did not support clock_gettime system call, which causes compilation error. You can modify the api.h so that you can test your code without time limitation.
- You can dump the input queries by output the contents of query array.
- The answers of each query is stored in testdata/test.ans
