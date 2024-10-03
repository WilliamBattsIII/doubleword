#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

extern char* registernames[];


enum {
    R0,
    R1,
    R2,
    R3,
    R4,
    R5,
    R6,
    R7,
    R8,
    R9,
    R10,
    R11,
    R12,
    R13,
    R14,
    R15,
    R16,
    R17,
    R18,
    R19,
    R20,
    R21,
    R22,
    R23,
    R24,
    R25,
    R26,
    R27,
    R28,
    R29,
    R30,
    R31,
    R32,
    R33,
    R34,
    R35,
    R36,
    R37,
    R38,
    R39,
    R40,
    R41,
    R42,
    R43,
    R44,
    R45,
    R46,
    R47,
    R48,
    R49,
    R50,
    R51,
    R52,
    R53,
    R54,
    R55,
    R56,
    R57,
    R58,
    R59,
    R60,
    R61,
    R62,
    R63,
    SP, // stack pointer
    IP, // instruction pointer
    ITP, // IVT pointer register
    SCR, // system control register
    MTP, // MAT pointer register
    NUM_REGISTERS // dummy register
};

enum {
    NOP = 0x00,
    ADD = 0x01,
    ADDI = 0x02,
    MUL = 0x03,
    IMUL = 0x04,
    DIV = 0x05,
    IDIV = 0x06,
    CMP = 0x07,
    ICMP = 0x08,
    BTS = 0x09,
    BTC = 0x0A,
    BTT = 0x0B,
    SLA = 0x0C,
    SRA = 0x0D,
    SRL = 0x0E,
    INC = 0x0F,
    DEC = 0x10,
    LDB = 0x11,
    LBW = 0x12,
    LDD = 0x13,
    STB = 0x14,
    STW = 0x15,
    STD = 0x16,
    HLT = 0x17,
    RET = 0x18,
    IRET = 0x19,
    ITE = 0x1A,
    ITD = 0x1B,
    SPL = 0x1C,
    LITP = 0x1D,
    LMTP = 0x1E,
    DEBUG = 0x1F,
    PUSH = 0x20,
    POP = 0x21,
    IN = 0x22,
    OUT = 0x23,
    ROR = 0x24,
    ROL = 0x25,
    AND = 0x26,
    NOT = 0x27,
    OR = 0x28,
    XOR = 0x29,
    SUB = 0x2A,
    ISUB = 0x2B,
    JMP = 0x2C,
    RJMP = 0x2D,
    RLAC = 0x2E,
    CALL = 0x2F,
    RCALL = 0x30,
    RSVD = 0x31
};


extern uint32_t registers[];


extern bool running;

#define MEMORY_SIZE_KB 32768 // 32 megabytes
#define PROC_SPEED_HZ 12500000 // 12.5 MHz

#define FPS 60 // frames per second
#define TPF 1 // ticks per frame
#define TPS (FPS * TPF) // ticks per second
#define CPF (PROC_SPEED_HZ / TPS)


extern uint8_t* memory;
extern uint64_t cyclecount;

void init_mem();
void exec_instruction(uint32_t instruction);
void emu_raise(uint8_t vector);
uint32_t get_instruction(uint32_t memory_address);
int calc_cycles(uint8_t opcode);
int emu_loop();