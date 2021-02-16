#include "utils.h"
#include "cstdlib"

using namespace std;

int main(int argc, char const* argv[]) {
    int* x[17];
    *x[0] = 1;
    int a,b;
    a = 3; b=4;
    cout<<sizeof(x)<<endl;
    cout<<*x[0]<<endl;
    cout<< Utils::addThree(3)<<endl;
    cout<< Utils::multiply(a,b)<<endl;
    return EXIT_SUCCESS; 
}

