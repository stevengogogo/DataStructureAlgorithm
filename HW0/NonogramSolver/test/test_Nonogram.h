/**
 * @file test_Nonogram.h
 */

#ifndef TEST_NONOGRAM_H
#define TEST_NONOGRAM_H

#include <string.h>
#include <time.h>
#include "acutest.h"
#include "NonogramSolver.h"

/** Measure the time spent*/
double time_elapse(clock_t begin,clock_t end){
    double time_spent = 0.0;
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    return time_spent;
}

/*Create a nonogram problem*/
void test_nonogram_struct(void){

    /*Create a nonogram problem*/
    int pLen[] = {1,1}; //Point lengths
    hint h = create_hint(pLen, 2);//Single hint
    hint hs[] = {h,h,h,h};
    hints H = create_hints(hs, 4);//all hints

    nogram nm; //nonogram probel
    size2D s = {
        .N=2,
        .M=2
    };//map size

    nm = init_nogram(nm, s, H);//init: map object, size and hints

    /*Verify information*/
    nm.map[0][0] = hole_val; //create psudo solution
    nm.map[0][1] = fill_val;
    char* hint_str;
    char* hint_str_real;
    char* nogram_str = create_nogram_str(nm);
    char* nogram_str_real = "_o\nUU\n";

    // Compare Hints
    for(int i=0;i<nm.Nhs.len;i++){
        TEST_ASSERT(comp_hint(nm.Nhs.h[i], H.h[i]) == 1);
    }
    for(int i=nm.Nhs.len;i<nm.Mhs.len;i++){
        TEST_ASSERT(comp_hint(nm.Mhs.h[i-nm.Nhs.len], H.h[i]) == 1);
    }

    //Test nogram map
    //TEST_ASSERT(striden(nogram_str_real, nogram_str) == 0);
    TEST_MSG("Real map: %s. \nBut got %s", nogram_str_real, nogram_str); 
    //print_nogram_str(nm);
    close_nogram_str(nogram_str);
}

void test_hint_printout(void){
    int pLens[] = {1,1,5,2};
    hint h= create_hint(pLens, 4);
    char *hstr = create_hint_str(h);
    printf("hint: %s ", hstr);
    print_hint_str(h);
    //Cleanup
    close_hint_str(hstr);
}

void test_map_display(void){
    nogram nog;
    //nog = create_nogram_scantf();
    nog = create_nogram_fscantf("test/data/input_1.txt");
    printf_map(nog);
}

void test_validity(void){
    int line1[]={1,1,1,1};
    int line2[]={1,1,0,1};
    int line3[]={0,1,0,0};
    int line4[]={1,1,1,0};
    int line5[]={0,0,0,0};

    TEST_ASSERT(segment_number(line1, 4, 1) == 1);
    TEST_ASSERT(segment_number(line2, 4, 1) == 2);
    TEST_ASSERT(segment_number(line3, 4, 1) == 1);
    TEST_ASSERT(segment_number(line4, 4, 1) == 1);
    TEST_ASSERT(segment_number(line5, 4, 1) == 0);
}

void test_create_nonogram(void){
    nogram nog;
    //nog = create_nogram_scantf();
    nog = create_nogram_fscantf("test/data/input_1.txt");

    TEST_ASSERT(nog.Nhs.h[0].nPoint == 2);
    TEST_ASSERT(nog.Nhs.h[1].nPoint == 2);
    TEST_ASSERT(nog.Nhs.h[2].nPoint == 2);
    TEST_ASSERT(nog.Nhs.h[3].nPoint == 1);
    TEST_ASSERT(nog.Mhs.h[0].nPoint == 2);
    TEST_ASSERT(nog.Mhs.h[1].nPoint == 2);
    TEST_ASSERT(nog.Mhs.h[2].nPoint == 2);
    TEST_ASSERT(nog.Mhs.h[3].nPoint == 2);
    // validate the content
    TEST_ASSERT(nog.size.N == 4);
    TEST_ASSERT(nog.size.M == 4);
    TEST_ASSERT(nog.Nhs.h[0].nPoint == 2);
}

void test_segment_measurement(void){
    struct array{
        int arr[4];
        int len;
        int n_seg;
    };

    struct array A[] = {
        {{0,0,0,0},4,0},
        {{1,0,0,0},4,1},
        {{0,1,0,0},4,1},
        {{1,1,0,0},4,1},
        {{0,0,1,0},4,1},
        {{1,0,1,0},4,2},
        {{0,1,1,0},4,1},
        {{1,1,1,0},4,1},
        {{0,0,0,1},4,1},
        {{1,0,0,1},4,2},
        {{0,1,0,1},4,2},
        {{1,1,0,1},4,2},
        {{0,0,1,1},4,1},
        {{1,0,1,1},4,2},
        {{0,1,1,1},4,1},
        {{1,1,1,1},4,1}
    };
    int A_len = 16;
    hint h;

    for(int i=0;i<A_len;i++){
        h = get_segments(A[i].arr, A[i].len);
        TEST_ASSERT(h.nPoint == A[i].n_seg);
    }

    h = get_segments(A[15].arr, A[15].len);
    TEST_ASSERT(h.pLens[0] == 4);

    h = get_segments(A[14].arr, A[14].len);
    TEST_ASSERT(h.pLens[0] == 3);
}

void test_verify_solution(void){
    nogram nog;

    //Input 1

    //nog = create_nogram_scantf();
    nog = create_nogram_fscantf("test/data/input_1.txt");

    int a0[4] = {1,0,1,0};
    int a1[4] = {0,1,0,1};
    int a2[4] = {1,0,1,0};
    int a3[4] = {1,1,1,1};

    for(int i=0;i<4;i++)
        nog.map[0][i] = a0[i];
    for(int i=0;i<4;i++)
        nog.map[1][i] = a1[i];
    for(int i=0;i<4;i++)
        nog.map[2][i] = a2[i];
    for(int i=0;i<4;i++)
        nog.map[3][i] = a3[i];

    TEST_ASSERT(is_nogram_valid(&nog) == 1);
}

void test_verify_solution2(void){
    nogram nog;
    // Input 2
    nog = create_nogram_fscantf("test/data/input_2.txt");

    int a0[] = {0,1,1,1,1};
    int a1[] = {1,1,0,0,0};
    int a2[] = {0,1,1,1,0};
    int a3[] = {0,0,0,1,1};
    int a4[] = {1,1,1,1,0};
    
    for(int i=0;i<5;i++)
        nog.map[0][i] = a0[i];
    for(int i=0;i<5;i++)
        nog.map[1][i] = a1[i];
    for(int i=0;i<5;i++)
        nog.map[2][i] = a2[i];
    for(int i=0;i<5;i++)
        nog.map[3][i] = a3[i];
    for(int i=0;i<5;i++)
        nog.map[4][i] = a4[i];
}

void read_file(void){

    FILE *stream = fopen("test/data/output_1.txt", "r");
    char line[80];
    int a;

    while ((fscanf(stream, "%[^\n]", line))!= EOF)
    {
        fgetc(stream); // Reads in '\n' character and moves file
        // stream past delimiting character
        for (int i=0;i<strlen(line);i++){
            a = convert_fill2num(line[i]);
            printf("%d", a);
        }
        printf("%s \n", line);
    }

    fclose(stream);
}

/** Use input and output file to create a valid nonogram. [Ground truth]*/
void test_create_nogram_with_answer(void){
    nogram nog;
    nog = create_nogram_with_answer("test/data/input_1.txt","test/data/output_1.txt");
}

void test_greedy_algorithm_fn(char* filename){
    //TODO
    nogram nog;
    
    nog = create_nogram_fscantf(filename);
    
    clock_t begin = clock();
    solve_nonogram(&nog);
    clock_t end = clock();
    printf("\nSolve test: %f sec\n", time_elapse(begin,end));

    TEST_ASSERT(is_nogram_valid(&nog) == 1);
    printf_map(nog);
}

//Solve
void test_greedy_algorithm(void){
    test_greedy_algorithm_fn("test/data/input_0.txt");

    test_greedy_algorithm_fn("test/data/input_col.txt");
    test_greedy_algorithm_fn("test/data/input_row.txt");
    test_greedy_algorithm_fn("test/data/input_long_line.txt");

    //test_greedy_algorithm_fn("test/data/input_blank.txt");

    test_greedy_algorithm_fn("test/data/input_filled.txt");

    test_greedy_algorithm_fn("test/data/input_1.txt");
    
    test_greedy_algorithm_fn("test/data/input_2.txt");

    test_greedy_algorithm_fn("test/data/input_3.txt");
    
    test_greedy_algorithm_fn("test/data/input_4.txt");
    test_greedy_algorithm_fn("test/data/input_5.txt");
    test_greedy_algorithm_fn("test/data/input_6.txt");
}



#endif