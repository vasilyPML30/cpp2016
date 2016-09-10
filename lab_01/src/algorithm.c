#include "util.h"
#include "io.h"

int doComputation(int a, int b)
{
  int c = max(a, b);
  logDebug("comp");
  return c;
}
