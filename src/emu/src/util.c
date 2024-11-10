#include "util.h"


// from = lower
// to = higher
// (MSB is 31, LSB is 0)
uint32_t extractbits(uint32_t orig, unsigned from, unsigned to) 
{
  unsigned mask = ( (1<<(to-from+1))-1) << from;
  return (orig & mask) >> from;
}
