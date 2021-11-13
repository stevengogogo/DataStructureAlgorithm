#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "GarbleFilter.h"
#include "utils.h"
#include "TextCompress.h"


int interface(){
    int N;
    char text[MAX_STR_LEN];
    char garble[MAX_STR_LEN];
    int textlen;
    int garblelen;
    scanf("%d", &N);

    for(int i=0;i<N;i++){

        scanf("%s", text);
        scanf("%s", garble);

        GarbleTextFilter(text, garble);
        DisplayCompressedText(text);

        //if(i!=N-1)
            printf("\n");
    }

    return 0;
}

int main()
{
    return interface();
}