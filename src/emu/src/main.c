#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "cpu.h"
// todo: utility file including extractbits() and a method to print binary

uint32_t extractbits(uint32_t orig, unsigned from, unsigned to) 
{
  unsigned mask = ( (1<<(to-from+1))-1) << from;
  return (orig & mask) >> from;
}

int main(void) { // TODO: program arguments to change size at runtime
    printf("Estimated emulated CPU cycles per second: %d\n", CPF);
    init_mem();
    emu_loop();
    return 0;
}
