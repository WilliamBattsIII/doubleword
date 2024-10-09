#include "cpu.h"
#include "util.h"

uint32_t registers [NUM_REGISTERS];
bool running = true;
uint8_t* memory;
uint64_t cyclecount = 0;

char* registernames[] = {
    "R0",
    "R1",
    "R2",
    "R3",
    "R4",
    "R5",
    "R6",
    "R7",
    "R8",
    "R9",
    "R10",
    "R11",
    "R12",
    "R13",
    "R14",
    "R15",
    "R16",
    "R17",
    "R18",
    "R19",
    "R20",
    "R21",
    "R22",
    "R23",
    "R24",
    "R25",
    "R26",
    "R27",
    "R28",
    "R29",
    "R30",
    "R31",
    "R32",
    "R33",
    "R34",
    "R35",
    "R36",
    "R37",
    "R38",
    "R39",
    "R40",
    "R41",
    "R42",
    "R43",
    "R44",
    "R45",
    "R46",
    "R47",
    "R48",
    "R49",
    "R50",
    "R51",
    "R52",
    "R53",
    "R54",
    "R55",
    "R56",
    "R57",
    "R58",
    "R59",
    "R60",
    "R61",
    "R62",
    "R63",
    "SP", // stack pointer
    "IP", // instruction pointer
    "ITP", // IVT pointer register
    "SCR",
    "MTP",
    "?????"
};

char* opcodenames[] = {
    "NOP",
    "ADD",
    "ADDI",
    "MUL",
    "IMUL",
    "DIV",
    "IDIV",
    "CMP",
    "ICMP",
    "BTS",
    "BTC",
    "BTT",
    "SLA",
    "SLA",
    "SRL",
    "INC",
    "DEC",
    "LDB",
    "LDW",
    "LDD",
    "STB",
    "STW",
    "STD",
    "HLT",
    "RET",
    "IRET",
    "ITE",
    "ITD",
    "SPL",
    "LITP",
    "LMTP",
    "DEBUG",
    "PUSH",
    "POP",
    "IN",
    "OUT",
    "ROR",
    "ROL",
    "AND",
    "NOT",
    "OR",
    "XOR",
    "SUB",
    "ISUB",
    "JMP",
    "RJMP",
    "CALL",
    "RCALL",
    "RSVD"
};

char *optypenames [] = {
    "REG_PTR_OR_NA",
    "REGISTER",
    "IMMED_B",
    "IMMED_PTR"
};

char *condcodenames[] = {
    "ALWAYS",
    "PLACEHOLDER1",
    "PLACEHOLDER2",
    "PLACEHOLDER3",
    "PLACEHOLDER4",
    "PLACEHOLDER5",
    "PLACEHOLDER6",
    "PLACEHOLDER7",
    "PLACEHOLDER8,"
    "PLACEHOLDER9",
    "PLACEHOLDER10",
    "PLACEHOLDER11",
    "PLACEHOLDER12",
    "PLACEHOLDER13",
    "PLACEHOLDER14",
    "PLACEHOLDER15"
};

void init_mem() {
    memory = malloc(MEMORY_SIZE_KB * 1024 * sizeof(uint8_t)); // set memory pointer
    for(int i = 0; i < NUM_REGISTERS; i++) {
        registers[NUM_REGISTERS] = 0; // properly zero out all registers
    }
    // todo: put test code or something in memory as a temporary way to get around loading files
}

int calc_cycles(uint8_t opcode) {
    // add logic to calculate cycles for things involving specific operand types?
    switch(opcode) {
        case NOP:
            return 1; /// TODO: struct for each opcode, contains cycles to execute - instead of this clusterfuck?
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
            return 12;
        case PUSH:
            return 2;
        case POP:
            return 2;
        case IN:
            return 4;
        case OUT:
            return 4;
        case ROR:
            return 1;
        case ROL:
            return 1;
        case AND:
            return 1;
        case NOT:
            return 1;
        case OR:
            return 1;
        case XOR:
            return 1;
        case SUB:
            return 1;
        case ISUB:
            return 1;
        case JMP:
            return 2;
        case RJMP:
            return 3;
        case RLAC:
            return 2;
        case CALL:
            return 6;
        case RCALL:
            return 6;
        case RSVD:
            return 5;
        default:
            return 0; // invalid instruction
    }
}
// MSB -> LSB || opcode, operand types, instruction-specific data, operand 1, operand 2
void exec_instruction(uint32_t instruction) {
    int cycles = 0;
    printf("Register dump:\n");
    for(int i = 0; i < NUM_REGISTERS; i++) { // print registers
        printf("%s: 0x%X\n", registernames[i], registers[i]);
    }
    printf("Instruction info:\nInstruction: 0x%X\n", instruction); // print instruction
    uint8_t opcode = extractbits(instruction, 26, 31); // opcode is at MSB
    cycles = calc_cycles(opcode);
    cyclecount += cycles;
    printf("Opcode: 0x%X (mnemonic: %s) (%d cycles)\n", opcode, opcodenames[opcode], cycles); // print opcode
    uint8_t typeA = extractbits(instruction, 24, 25);
    uint8_t typeB = extractbits(instruction, 22, 23);
    uint8_t cond_code = extractbits(instruction, 16, 21);
    uint8_t operandA = extractbits(instruction, 8, 15);
    uint8_t operandB = extractbits(instruction, 0, 7);
    printf("A operand type: %s\n", optypenames[typeA]);
    printf("B operand type: %s\n", optypenames[typeB]);
    printf("Condition code: %s\n", condcodenames[cond_code]);
    printf("A operand value: 0x%X\n", operandA);
    printf("B operand value: 0x%X\n", operandB);
}
void emu_raise(uint8_t vector) {}

// note for below: memory_address is from the emulator, and is really an index into the "real" memory pointer
uint32_t get_instruction(uint32_t memory_address) {
    if(memory_address % 4 == 0) {
        // logic goes here
    }
    else {
        emu_raise(0x06); // raise Alignment Fault
    }
    return 0; // placeholder, remove this
}

int emu_loop() {
    while(running) {
        //uint32_t instruction = get_instruction(registers[IP]);
        
        exec_instruction(0x8A80CDE7);
        running = false;
    }
    return 0;
}