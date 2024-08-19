#include <stdio.h>
#include <stdint.h>

#define MEMORY_SIZE_KB 32768 // 32 megabytes

#define FPS 60 // probably gonna be useful for when I get a display library set up
#define TPF 1 // ticks per frame
#define TPS (FPS * TPF) // ticks per second is nice to know

uint8_t* memory;

typedef enum {
    R0, // zero constant

    SP, // stack pointer
    IP, // instruction pointer
    ITP, // interrupt table pointer
    SCR, // system control register
    NUM_REGISTERS // dummy register
};

uint32_t registers [NUM_REGISTERS];

int main(void) {
    memory =  malloc(MEMORY_SIZE_KB * 1024 * sizeof(uint8_t)); // TODO: program arguments to change size at runtime
    return 0;
}