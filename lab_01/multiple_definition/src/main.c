#include "util.h"
#include "io.h"
#include "algorithm.h"

int max(int a, int b)
{
  return a > b ? a : b;
}

int main()
{
  int a = doComputation(5, 7); 
  int b = 5;
  max(a, b);
  logDebug("main");
  return 0;   
}
