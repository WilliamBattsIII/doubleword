#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MEMORY_SIZE_KB 32768 // 32 megabytes

extern uint8_t* memory;

void init_mem();