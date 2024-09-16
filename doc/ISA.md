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

### 0x00: nop (no operation)
Opcode: `000000`

Instruction-specific bitfield use?: No

Function: Does nothing

Modifies flags?: No
### 0x01: add (addition)
Opcode: `000001`

Instruction-specific bitfield use?: No

Function: Adds values from two registers and stores it in the `src` operand register if two registers are provided as operands. Otherwise, if one register and one immediate value is provided, the result will be stored in the register provided.

Modifies flags?: Only with `.s` suffix
### 0x02: addi (signed addition)

### 0x03: mul (multiply)
### 0x04: imul (signed multiply)
### 0x05: div (division)
### 0x06: idiv (signed division)
### 0x07: cmp (compare)
### 0x08: icmp (signed compare)
### 0x09: bts (bit set)
### 0x0A: btc (bit clear)
### 0x0B: btt (test if bit set)
### 0x0C: sla (bitshift left)
### 0x0D: sra (shift right aritmetic)
### 0x0E: srl (shift right logical)
### 0x0F: inc (increment)
### 0x10: dec (decrement)
### 0x11: ldb (load byte)
### 0x12: lbw (load word)
### 0x13: ldd (load dword)
### 0x14: stb (store byte)
### 0x15: stw (store word)
### 0x16: std (store dword)
### 0x17: call (call subroutine)
### 0x18: ret (return from subroutine)
### 0x19: iret (return from interrupt)
### 0x1A: ite (enable interrupt bit)
### 0x1B: itd (disable interrupt bit)
### 0x1C: spl (set CPU privilege level)
### 0x1D: litp (load %itp)
### 0x1E: lmtp (load %mtp)
### 0x1F: debug (debug instruction)
### 0x20: push (push to stack)
### 0x21: pop (pop from stack)
### 0x22: in (get dword from i/o port)
### 0x23: out (send dword to i/o port)
### 0x24: hlt (halt CPU)