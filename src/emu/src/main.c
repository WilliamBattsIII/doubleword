#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "cpu.h"


#define MEMORY_SIZE_KB 32768 // 32 megabytes
#define PROC_SPEED_HZ 12500000 // 12.5 MHz

#define FPS 60 // frames per second
#define TPF 1 // ticks per frame
#define TPS (FPS * TPF) // ticks per second
#define CPF (PROC_SPEED_HZ / TPS)


uint8_t* memory;

int main(void) {
    memory =  malloc(MEMORY_SIZE_KB * 1024 * sizeof(uint8_t)); // TODO: program arguments to change size at runtime
    printf("%d\n", CPF);
    return 0;
}
