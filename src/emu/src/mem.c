#include "mem.h"

uint8_t* memory;

void init_mem() {
    memory = malloc(MEMORY_SIZE_KB * 1024 * sizeof(uint8_t)); // set memory pointer
    // todo: put test code or something in memory as a temporary way to get around loading files
}

uint32_t getdword(uint32_t addr) {
    if(addr % 4 == 0) {
        // logic goes here
    }
    else {
        emu_raise(0x06); // raise Alignment Fault
    }
}

uint16_t getword(uint32_t addr) {
    if(addr % 2 == 0) {
        
    }
    else {
        emu_raise(0x06); // raise Alignment Fault
    }
}

uint8_t getbyte(uint32_t addr) {
    return memory[addr];
}