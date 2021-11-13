#include "utils.h"


int is_double_equal(double a, double b){
    double tol = 0.000000000001;
    double diff = fabs(a - b) / max_double(1, fabs(b));
    if (diff <=  tol )
        return 1;
    else
        return 0;
}

double max_double(double a, double b){
    if (a>=b)
        return a;
    else
        return b;
}







