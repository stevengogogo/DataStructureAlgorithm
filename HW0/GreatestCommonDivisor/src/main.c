#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/bigint.h"

#define MAX_DEC 257

int main()
{   
    char a[257], b[257];
    bigint gcd;
    bigint aB, bB;
    scanf("%s %s", a, b);
    aB = newnumc(a);
    bB = newnumc(b); 
    gcd = gcd_bigint(aB, bB);
    printf("%s\n", create_string(gcd));

    return 0;
}