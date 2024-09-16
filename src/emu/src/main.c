#include <stdio.h>
#include <stdint.h>

#include "cpu.h"


#define MEMORY_SIZE_KB 32768 // 32 megabytes

#define FPS 60 // probably gonna be useful for when I get a display library set up
#define TPF 1 // ticks per frame
#define TPS (FPS * TPF) // ticks per second is nice to know

uint8_t* memory;

int main(void) {
    memory =  malloc(MEMORY_SIZE_KB * 1024 * sizeof(uint8_t)); // TODO: program arguments to change size at runtime
    return 0;
}
