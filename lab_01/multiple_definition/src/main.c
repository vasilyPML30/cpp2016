#include "util.h"
#include "io.h"
#include "algorithm.h"

int main()
{
  int a = doComputation(5, 7); 
  int b = 5;
  max(a, b);
  logDebug("main");
  return 0;   
}
