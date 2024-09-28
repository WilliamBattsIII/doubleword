#include "cpu.h"


uint32_t registers [NUM_REGISTERS];
bool running = true;
uint8_t* memory;
uint64_t cyclecount = 0;
void init_mem() {
    memory = malloc(MEMORY_SIZE_KB * 1024 * sizeof(uint8_t)); // set memory pointer
}

int calc_cycles(uint8_t opcode) {
    // add logic to calculate cycles for things involving specific operand types
    switch(opcode) {
        case NOP:
            return 1; /// TODO: struct for each opcode, contains cycles to execute?
        case ADD:
            return 1;
        case ADDI:
            return 1;
        case MUL:
            return 1;
        case IMUL:
            return 1;
        case DIV:
            return 1;
        case IDIV:
            return 1;
        case CMP:
            return 2;
        case ICMP:
            return 2;
        case BTS:
            return 2;
        case BTC:
            return 2;
        case BTT:
            return 2;
        case SLA:
            return 1;
        case SRA:
            return 1;
        case SRL:
            return 1;
        case INC:
            return 1;
        case DEC:
            return 1;
        case LDB:
            return 5;
        case LBW:
            return 5;
        case LDD:
            return 5;
        case STB:
            return 5;
        case STW:
            return 5;
        case STD:
            return 5;
        case HLT:
            return 1;
        case RET:
            return 3;
        case IRET:
            return 3;
        case ITE:
            return 1;
        case ITD:
            return 1;
        case SPL:
            return 3;
        case LITP:
            return 1;
        case LMTP:
            return 1;
        case DEBUG:
        case PUSH:
        case POP:
        case IN:
        case OUT:
        // TODO: other instructions
        default:
            return -1; // invalid instruction
    }
}

void exec_instruction(uint32_t instruction) {}
void emu_raise(uint8_t vector) {}


uint32_t get_instruction(uint32_t memory_address) {
    if(memory_address % 4 == 0) {
        // logic goes here
    }
    else {
        emu_raise(0x06);// raise Alignment Fault
    }
    return 0; // placeholder, remove this
}

int emu_loop() {
    while(running) {
        uint32_t instruction = get_instruction(registers[IP]);
        cyclecount += calc_cycles(instruction);
        exec_instruction(instruction);
        running = false;
    }
    return 0;
}