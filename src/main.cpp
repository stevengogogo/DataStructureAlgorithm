#include "utils.h"
#include "cstdlib"
using namespace std;

int main(int argc, char const* argv[]) {
    int* x[17];
    *x[0] = 1;
    cout<<sizeof(x)<<endl;
    cout<<*x[0]<<endl;
    return EXIT_SUCCESS; 
}

