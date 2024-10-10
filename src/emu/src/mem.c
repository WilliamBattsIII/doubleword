#include "mem.h"

uint8_t* memory;

void init_mem() {
    memory = malloc(MEMORY_SIZE_KB * 1024 * sizeof(uint8_t)); // set memory pointer
    // todo: put test code or something in memory as a temporary way to get around loading files
}
