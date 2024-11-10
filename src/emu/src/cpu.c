#include "cpu.h"
#include "util.h"
#include "mem.h"

uint32_t registers [NUM_REGISTERS];
bool running = true;

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

void init_reg() {
    for(int i = 0; i < NUM_REGISTERS; i++) {
        registers[NUM_REGISTERS] = 0; // properly zero out all registers
    }   
}

void set_bit(int reg, int bit, bool value) {
    if(value) { // set bit
        registers[reg] |= 1 << bit;
    }
    else { // clear bit
        registers[reg] &= ~(1 << bit); 
    }
}

void set_mat_granulatity(int value) {
    switch(value) {
        case MAT_DISABLED: // 00
            set_bit(SCR, 16, false);
            set_bit(SCR, 17, false);
            break;
        case MAT_4K: // 01
            set_bit(SCR, 16, false);
            set_bit(SCR, 17, true);
            break;
        case MAT_16K: // 10
            set_bit(SCR, 16, true);
            set_bit(SCR, 17, false);
            break;
        case MAT_64K: // 11
            set_bit(SCR, 16, true);
            set_bit(SCR, 17, true);
            break;
        default: // shouldn't even be possible haha
            break;
    }
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
// debug
void dump_registers() {
    printf("Register dump:\n");
    for(int i = 0; i < NUM_REGISTERS; i++) { // print registers
        printf("%s: 0x%X\n", registernames[i], registers[i]);
    }
}
// debug
void print_instruction_info(uint32_t instr, uint8_t opc, uint8_t cyc, uint8_t ta, uint8_t tb, uint8_t cc,  uint8_t oa, uint8_t ob) {
    printf("Cycle #%ld\n\n", cyclecount);
    printf("Instruction: 0x%X\n", instr); 
    printf("Opcode: 0x%X (mnemonic: %s) (%d cycles)\n", opc, opcodenames[opc], cyc); // print opcode
    printf("A operand type: %s\n", optypenames[ta]);
    printf("B operand type: %s\n", optypenames[tb]);
    printf("Condition code: %s\n", condcodenames[cc]);
    printf("A operand value: 0x%X\n", oa);
    printf("B operand value: 0x%X\n", ob);
}
// MSB -> LSB || opcode, operand types, instruction-specific data, operand 1, operand 2
void exec_instruction(uint32_t instruction) {
    int cycles = 0;
    // print instruction
    uint8_t opcode = extractbits(instruction, 26, 31); // opcode is at MSB
    uint8_t typeA = extractbits(instruction, 24, 25);
    uint8_t typeB = extractbits(instruction, 22, 23);
    uint8_t instr_info = extractbits(instruction, 21, 20);
    uint8_t cond_code = extractbits(instruction, 16, 19);
    

    uint8_t operandA = extractbits(instruction, 8, 15);
    uint8_t operandB = extractbits(instruction, 0, 7);
    
    cycles = calc_cycles(opcode);
    //dump_registers(); // this and the following line is debug stuff
    print_instruction_info(instruction, opcode, cycles, typeA, typeB, cond_code, operandA, operandB);
    switch(opcode) {
        case NOP:
            break;
        case ADD:
            if(typeA == REGISTER && typeB == REGISTER) {
                
                if(instr_info == 0b01) { // add.s -> modify flags
                    if(((registers[operandA] + registers[operandB]) % 2^32) < (registers[operandA] % 2^32) || ((registers[operandA] + registers[operandB]) % 2^32) < (registers[operandB] % 2^32)) { //a + b mod 2^n < a mod 2^n OR a + b mod 2^n < b mod 2^n
                        // set carry flag (the overflow flag is only for signed arithmetic)
                    } 
                    //if() {} zero
                    //if() {} parity
                }
                registers[operandB] = registers[operandA] + registers[operandB]; // do this last, so nothing breaks
            }
            else {
                emu_raise(0x07); // invalid instruction
            }
            break;  
        case ADDI:
            break;  
        case MUL:
            break;  
        case IMUL:
            break;  
        case DIV:
            break;  
        case IDIV:
            break;  
        case CMP:
            break;  
        case ICMP:
            break;  
        case BTS:
            break;  
        case BTC:
            break;  
        case BTT:
            break;  
        case SLA:
            break;  
        case SRA:
            break;  
        case SRL:
            break;  
        case INC:
            break;  
        case DEC:
            break;  
        case LDB:
            break;  
        case LBW:
            break;  
        case LDD:
            break;  
        case STB:
            break;  
        case STW:
            break;  
        case STD:
            break;  
        case HLT:
            break;  
        case RET:
            break;  
        case IRET:
            break;  
        case ITE:
            break;  
        case ITD:
            break;  
        case SPL:
            break;  
        case LITP:
            break;  
        case LMTP:
            break;  
        case DEBUG:
            break; 
        case PUSH:
            break;  
        case POP:
            break;  
        case IN:
            break;  
        case OUT:
            break;  
        case ROR:
            break;  
        case ROL:
            break;  
        case AND:
            break;  
        case NOT:
            break;  
        case OR:
            break;  
        case XOR:
            break;  
        case SUB:
            break;  
        case ISUB:
            break;  
        case JMP:
            break;  
        case RJMP:
            break;  
        case RLAC:
            break;  
        case CALL:
            break;  
        case RCALL:
            break;  
        case RSVD:
            break;  
        default:
            break;   // invalid instruction
    }
    registers[IP] += cycles;
}

void emu_raise(uint8_t vector) {} // raise an interrupt

// note for below: memory_address is from the emulator, and is really an index into the "real" memory pointer
uint32_t get_instruction(uint32_t memory_address) {
    return read_dword(memory_address);
}

void mem_rw_test() {
    uint32_t addr = 0x0001000;
    uint32_t dword = 0xAABBCCDD;
    printf("\nWriting dword 0x%X\n", dword);
    write_dword(dword, addr);
    printf("Memory read: 0x%X\n", read_dword(addr));

    uint32_t word = 0x1234;
    printf("\nWriting word 0x%X\n", word);
    write_dword(word, addr);
    printf("Memory read: 0x%X\n", read_word(addr));

    uint32_t byte = 0xAB;
    printf("\nWriting byte 0x%X\n", byte);
    write_byte(byte, addr);
    printf("Memory read: 0x%X\n", read_byte(addr));
}
void mat_gtest() {
    printf("0x%X\n", registers[SCR]); 
    set_mat_granulatity(MAT_DISABLED);
    printf("0x%X\n", registers[SCR]); 
    set_mat_granulatity(MAT_4K);
    printf("0x%X\n", registers[SCR]); 
    set_mat_granulatity(MAT_16K);
    printf("0x%X\n", registers[SCR]); 
    set_mat_granulatity(MAT_64K);
    printf("0x%X\n", registers[SCR]);                
}


int emu_loop() {
    while(running) {
        uint32_t instruction = get_instruction(memory[registers[IP]]);
        exec_instruction(instruction);
        // if debug port has byte: print character
        //mem_rw_test();
        //mat_gtest();
        running = false;
    }
    return 0;
}