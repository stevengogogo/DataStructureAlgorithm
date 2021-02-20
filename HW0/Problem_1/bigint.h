typedef unsigned int digit; 
#define MAX_DEC 256 

typedef struct 
{
    digit number[MAX_DEC];
    int length;
} bigint; 

bigint* newnumc(char*);

void print(bigint*);

char* string(bigint*);

int str2int(char);