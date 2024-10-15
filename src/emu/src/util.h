#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

uint32_t extractbits(uint32_t orig, unsigned from, unsigned to);
char *stringifybits(uint32_t value); // print bits?