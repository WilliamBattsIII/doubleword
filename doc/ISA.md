# doubleword ISA

## Assembly info:
### ordering
Examples:
`add %r1, %r2`
`ldw %r1, [%r2]`
`push program_label`
`jmp program_label`
`jmp [%r17]`
In `doubleword` assembly, the opcode goes first, and is followed by operands. The target operand comes before the source operand, and may be followed by certain values, such as with immediates, or modifiers.
### jumping to addresses
Despite the inability to jump
### indicators
There are various indicators within the `doubleword` assembly language, mainly used to make writing an assembler easier.

Brackets around a label or register signify that the value is a pointer.
For example, say `%r2` is a register containing a memory address, and the memory at that address contains the character `A`. If you wanted to load `%r1` with the contents of the memory address in `%r2,` you could dereference the pointer with `ldb %r1, [%r2]`.

A percent character before an operand indicates that it's a register. As an example, `%sp`, `%itp`, and `%r39` are all registers.

If a number begins with `0x` or ends with `h`, it is to be treated as a hexadecimal number. If a number begins with `b`, it is to be treated as a binary number.

### 0x00: nop
Opcode: `000000`

Instruction-specific bitfield use?: No

Function: Does nothing

Modifies flags?: No
### 0x01: add
Opcode: `000001`

Instruction-specific bitfield use?: No

Function: Adds values from two registers and stores it in the `src` operand register

Modifies flags?: Only with `.s` suffix
### 0x02: addi
Opcode: `000002`

Instruction-specific bitfield use?: No

Function: Adds two values (one register, one immediate), and stores it in the register operand

Modifies flags?: Only with `.s` suffix
### 0x03:
### 0x04
### 0x05
### 0x06
### 0x07
### 0x08
### 0x09
### 0x0A
### 0x0B
### 0x0C
### 0x0D
### 0x0E
### 0x0F
### 0x10