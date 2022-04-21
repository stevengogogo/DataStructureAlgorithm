#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "acutest.h"
#include "utils.h"
#include "Utility.h"
#include <string.h>
#include <time.h>

void test_utils(void)
{
    int a, b;
    a = 1; b= 2;
    TEST_CHECK(argmax(a,b)  == 1 );
    TEST_CHECK(argmax(b,a) == 0);
    TEST_CHECK(argmax(1,1) == 1);
}

void readmail(void){
    int num_mail;
    mail* mails;
    clock_t str;
    clock_t end;

    str = clock();
    get_mails("test/data/test.in", &mails, &num_mail);
    end = clock();
    print_clock("Read Email:", str, end);

    TEST_CHECK(mails[0].id == 0); 
    TEST_MSG("Got %d\n", mails[0].id);
    TEST_CHECK(strncmp(mails[0].from, "Tim", strlen(mails[0].from)-1)==0); 
    TEST_MSG("Got %s\n", mails[0].from);
    TEST_CHECK(strncmp(mails[0].content, "Minas-Rio is an iron ore mining project in Brazil.[1] It is one of the world's largest mining projects, and is initially expected to export 26.5 million tonnes of iron ore in 2013, through a 525km slurry pipeline to a port at Au;[2] production potential is 53 Mtpa or higher.[3] The project was bought by Anglo American PLC, which is facing high costs.[4][5] The mine has certified reserves of 4.6 billion tonnes of itabirite.[6] There have been delays in starting the project, but in December 2010, Anglo American obtained a key license needed from Brazilian government before mining could start.[7][8]  I read the paragraph on http://wikipedia.org ", strlen(mails[0].content)-1)==0); 
    TEST_MSG("Got %s\n", mails[0].content);
    TEST_CHECK(strncmp(mails[0].subject, "Minas-Rio", strlen(mails[0].subject)-1)==0); 
    TEST_MSG("Got %s\n", mails[0].subject);
    TEST_CHECK(strncmp(mails[0].to, "Tony", strlen(mails[0].to)-1)==0); 
    TEST_MSG("Got %s\n", mails[0].to);

    free(mails);
}

void test_power(void){
    TEST_CHECK(power_int(4,0)==1);
    TEST_CHECK(power_int(4,1)==4);
    TEST_CHECK(power_int(4,2)==16);
    TEST_CHECK(power_int(4,3)==64);
}

void test_char2num(void){
    TEST_CHECK(char2num('0') == 0);
    TEST_CHECK(char2num('1') == 1);
    TEST_CHECK(char2num('2') == 2);
    TEST_CHECK(char2num('3') == 3);
    TEST_CHECK(char2num('4') == 4);
    TEST_CHECK(char2num('5') == 5);
    TEST_CHECK(char2num('6') == 6);
    TEST_CHECK(char2num('7') == 7);
    TEST_CHECK(char2num('8') == 8);
    TEST_CHECK(char2num('9') == 9);
    TEST_CHECK(char2num('a') == 10);
    TEST_CHECK(char2num('b') == 11);
    TEST_CHECK(char2num('c') == 12);
    TEST_CHECK(char2num('d') == 13);
    TEST_CHECK(char2num('e') == 14);
    TEST_CHECK(char2num('f') == 15);
    TEST_CHECK(char2num('g') == 16);
    TEST_CHECK(char2num('h') == 17);
    TEST_CHECK(char2num('i') == 18);
    TEST_CHECK(char2num('j') == 19);
    TEST_CHECK(char2num('k') == 20);
    TEST_CHECK(char2num('z') == 35);
    TEST_CHECK(char2num('A') == (int)('A'));
}

void test_sort(void){
    int len = 11;
    int* arrSorted =(int*)malloc(len*sizeof(int));
    int* arrOrg =(int*)malloc(len*sizeof(int));
    //Increasing order
    int ArrSorted[11] = {0,1,2,3,4,5,6,7,8,9,10};
    int ArrOrg[11] = {2,3,1,4,7,5,6,8,10,9,0};

    for(int i=0;i<len;i++){
        arrSorted[i] = ArrSorted[i];
        arrOrg[i] = ArrOrg[i];
    }
    
    quicksort(arrOrg, 0, len-1);

    for(int i =0; i<len;i++){
        TEST_CHECK(arrSorted[i] == arrOrg[i]);
        TEST_MSG("Got %d, Expedted %d", arrSorted[i],arrOrg[i]);
    }

    free(arrSorted);
    free(arrOrg);
}

void test_matrix(void){
    Matrix M;
    init_Matrix(&M, 2, 2);
    set_Matrix(&M, 0,0,1);
    TEST_CHECK(get_Matrix(&M, 0, 0) == 1);
    TEST_CHECK(get_Matrix(&M, 0, 1) == 0);
    TEST_CHECK(get_Matrix(&M, 1, 0) == 0);
    TEST_CHECK(get_Matrix(&M, 1, 1) == 0);
    kill_Matrix(&M);
}


#endif