#ifndef TEST_TEXTCOMPRESS_H
#define TEST_TEXTCOMPRESS_H
#include "acutest.h"
#include "TextCompress.h"
#include "utils.h"
#include <string.h>

void text_hash(void){
    que pinT;
    que pinH;

    char text[2000]="okayokayokay\0";
    int textlen = strlen(text);
    TextCompressMark(text, textlen, &pinT, &pinH);

    TEST_CHECK(text[strlen(text)]=='\0');
    TEST_CHECK(pinT.head == 0); TEST_MSG("Got %d", pinT.head);
    TEST_CHECK(pinH.head == 0); TEST_MSG("Got %d", pinH.head);
    TEST_CHECK(pinT.tail == 0); TEST_MSG("Got %d", pinT.tail);
    TEST_CHECK(pinH.tail == 0); TEST_MSG("Got %d", pinH.tail);

    TEST_CHECK(peek_que(&pinT) == 3);
    TEST_CHECK(peek_que(&pinH) == 8);

    PrintCompressedText(text, textlen, &pinT, &pinH);

    kill_que(&pinT);
    kill_que(&pinH);
}

void text_compressed(void){
    que pinT;
    que pinH;

    char text[2000]="JJJJJJ\0";
    int textlen = strlen(text);
    TextCompressMark(text, textlen, &pinT, &pinH);


    TEST_CHECK(pinT.head == 0); TEST_MSG("Got %d", pinT.head);
    TEST_CHECK(pinH.head == 0); TEST_MSG("Got %d", pinH.head);
    TEST_CHECK(pinT.tail == 2); TEST_MSG("Got %d", pinT.tail);
    TEST_CHECK(pinH.tail == 2); TEST_MSG("Got %d", pinH.tail);

    TEST_CHECK(peek_que(&pinT) == 0);
    TEST_CHECK(peek_que(&pinH) == 5);

    PrintCompressedText(text, textlen, &pinT, &pinH);

    kill_que(&pinT);
    kill_que(&pinH);
}

void test_compressed2(void){
    que pinT;
    que pinH;

    char text[4000]="CCRRRWCRRRRRWQAWRVRCECCrCCRCWWWVWgCCCCCCiCCEWRCCCRCRWRRRRCWWWWRCCWWRRWCWRRWUWRCRCRWCWWgWWRRoWCWTCRRCWWCRWWRCWCCRCCCCRNWCRCRWcRWCXWRCRWWCCWRRRVWWRCCCCOCDCCCWRWCRRWCURhWCRRCCWCRRCWRCWFRRCRRCRCNWRCCCCOCRCRRCCCRRCRCWRWCWRCCCCDCRWRCCWCWCWCCCRRCWRWWCWCCWZRkRWCRCjMRRCWRCWVCWYWCWCWVCRRCCRRNWaJECRCCWCWWRCCRnRRRWWCCCRRRWCWoWCdCRCECCCWWRCCWCCWRRCRWRRWRjWRCmCWnCRCCRRWWRWCKCRRWRgWWWCtRWNCGARWCCrRCCRCrWCCRRCWiHWWWWRCRWRRJDCCCBRRWRRpCWWRRRRRsCCnRWRWRCCRRCCCWCRCCWxRRWRPCWWRRRWWRCCWRRWRWCRHCbCRCRRRCCWCRCWRWRWWCWCWCCWWCWCCWRWWWRCCWRWWWRWdCRCaRRNERCRWMRRWRCNCRRkCyWCRCCWRWCCCRWiRCWCCRWWRWCRRWWCCCWWRCRCRRCCRRRLhORRWCWJCRWCWNUWCpWECWCWWCCCWeCRRRRCCCRMCRWWRHCWCiCWCCCRPRRcWCWWCWWHFWCRaRCCRR\0";

    TextCompressMark(text, strlen(text), &pinT, &pinH);
    TEST_CHECK(pinT.arr.len == 2); TEST_MSG("Got %d", pinT.arr.len);
    TEST_CHECK(pinH.arr.len == 2); TEST_MSG("Got %d", pinH.arr.len);

    TEST_CHECK(pinT.arr.i[0] == 3);
    TEST_CHECK(pinT.arr.i[1] == 4);

}

#endif