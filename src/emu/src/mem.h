#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MEMORY_SIZE_KB 32768 // 32 megabytes

extern uint8_t* memory;

void init_mem();

uint32_t getdword(uint32_t addr);
uint16_t getword(uint32_t addr);
uint8_t getbyte(uint32_t addr);