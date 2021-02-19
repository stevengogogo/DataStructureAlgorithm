#include "acutest.h"
#include "../bigint.h"

void
test_tutorial(void)
{
    void* mem;
    int a=1;

    mem = malloc(10);
    TEST_CHECK(mem != NULL);

    mem = realloc(mem, 20);
    TEST_CHECK(mem != NULL);
    

    free(mem);

    
}


void
test_fail(void)
{
    int a, b;

    /* This condition is designed to fail so you can see what the failed test
     * output looks like. */
    a = 1;
    b = 2;
    TEST_CHECK(a + b == 5);

    /* Here is TEST_CHECK_ in action. */
    TEST_CHECK_(a + b == 5, "%d + %d == 5", a, b);

    /* We may also show more information about the failure. */
    if(!TEST_CHECK(a + b == 5)) {
        TEST_MSG("a: %d", a);
        TEST_MSG("b: %d", b);
    }

    /* The macro TEST_MSG() only outputs something when the preceding
     * condition fails, so we can avoid the 'if' statement. */
    TEST_CHECK(a + b == 3);
    TEST_MSG("a: %d", a);
    TEST_MSG("b: %d", b);
}


// Run TESTs 
TEST_LIST = {
    { "tutorial", test_tutorial },
    {"Fail test", test_fail},
    {NULL, NULL} // Terminate the test
};