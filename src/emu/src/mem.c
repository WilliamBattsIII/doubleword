#include "mem.h"

uint8_t memory[32768 * 1024] = {0};

void init_mem() {
    // nothing, for now
    // todo: put test code or something in memory as a temporary way to get around loading files
}

uint32_t read_dword(uint32_t addr) {
    uint32_t cont = 0; // contents to be returned
    if(addr % 4 == 0) {
        cont = (memory[addr+3] << 24) | 
        (memory[addr+2] << 16) | 
        (memory[addr+1] << 8) | 
        (memory[addr]);
        return cont;
    }
    else {
        emu_raise(0x06); // raise Alignment Fault
    }
}
uint16_t read_word(uint32_t addr) {
    uint16_t cont = 0;
    if(addr % 2 == 0) {
        cont = (memory[addr+1] << 8) | 
        (memory[addr]);
    }
    else {
        emu_raise(0x06); // raise Alignment Fault
    }
}

uint8_t read_byte(uint32_t addr) {
    return memory[addr];
}

void write_dword(uint32_t contents, uint32_t addr) {
    if(addr % 4 == 0) {
        memory[addr] = extractbits(contents, 0,7);
        memory[addr+1] = extractbits(contents, 8,15);
        memory[addr+2] = extractbits(contents, 16,23);
        memory[addr+3] = extractbits(contents, 24,31);
    }
    else {
        emu_raise(0x06); // raise Alignment Fault
    }
}

void write_word(uint16_t contents, uint32_t addr) {
    if(addr % 2 == 0) {
        
    }
    else {
        emu_raise(0x06); // raise Alignment Fault
    }
}

void write_byte(uint8_t contents, uint32_t addr) {
    memory[addr] = contents;
}