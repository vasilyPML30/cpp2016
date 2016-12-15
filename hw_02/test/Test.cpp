#include "Test.h"

int Test::failedNum = 0;
int Test::totalNum = 0;

void Test::check(bool expr, const char *func, const char  *filename, size_t lineNum)
{
    totalNum++;
    if (!expr)
    {
        printf("test failed: %s() in %s:%lu\n", func, filename, lineNum);
        failedNum++;
    }
}

void Test::showFinalResult()
{
    if (!failedNum)
        printf("All tests passed.\n");
    else
        printf("Failed %i of %i tests.\n", failedNum, totalNum);
}