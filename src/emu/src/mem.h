#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "cpu.h"

//#define MEMORY_SIZE_KB 32768 // 32 megabytes

extern uint8_t memory[];

void init_mem();

uint32_t read_dword(uint32_t addr);
uint16_t read_word(uint32_t addr);
uint8_t read_byte(uint32_t addr);

void write_dword(uint32_t contents, uint32_t addr);
void write_word(uint16_t contents, uint32_t addr);
void write_byte(uint8_t contents, uint32_t addr);