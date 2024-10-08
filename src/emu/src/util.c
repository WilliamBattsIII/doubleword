#include "util.h"

uint32_t extractbits(uint32_t orig, unsigned from, unsigned to) 
{
  unsigned mask = ( (1<<(to-from+1))-1) << from;
  return (orig & mask) >> from;
}
