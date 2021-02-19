# define CHARZERO_ABOVEINTZERO 48

typedef unsigned char digit; 

typedef struct 
{
    digit* number;
    int length;
} bigint; 

bigint* newnumc(char*);
