#include <stdio.h>
#include <stdint.h>

#define MEMORY_SIZE_KB 32768 // 32 megabytes

#define FPS 60 // probably gonna be useful for when I get a display library set up
#define TPF 1
#define TPS (FPS * TPF)

uint8_t* memory;

typedef enum {
    R0, // zero constant
    R1,
    R2,
    R3,
    R4,
    R5,
    R6,
    R7,
    SP, // stack pointer
    IP, // instruction pointer
    ITP, // interrupt table pointer
    SCR, // system control register
    NUM_REGISTERS // dummy register
};

uint32_t registers [NUM_REGISTERS];

int main(void) {
    memory =  malloc(MEMORY_SIZE_KB * 1024 * sizeof(uint8_t)); // TODO: program arguments to change size at runtime
    printf("don't run this on a powerPC :^)\n");
    return 0;
}