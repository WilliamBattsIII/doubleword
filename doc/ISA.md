# doubleword ISA

## Assembly info:
### ordering
Examples:

`add %r1, %r2`

`ldw %r1, [%r2]`

`push program_label`

`jmp program_label`

`jmp [%r17]`


In `doubleword` assembly, the opcode mnemonic comes first in the instruction, and is followed by operands.

The target operand comes before the source operand, and may be followed by certain values, such as with immediates, or modifiers.

The target operand is usually the location where the result of the instruction will be stored. This differs if the target operand is not a register, or if alternate behavior is specified.
### jumping to addresses
Despite the inability to jump via immediate arguments, any jump instruction can jump to any memory address, as long as the correct CPU privilege is set.
### assembler conventions
There are various indicators and conventions within the `doubleword` assembly language, mainly used to make writing the assembler easier.

Brackets around a label or register signify that the value is a pointer.
For example, say `%r2` is a register containing a memory address, and the memory at that address contains the character `A`. If you wanted to load `%r1` with the contents of the memory address in `%r2,` you could dereference the pointer with `ldb %r1, [%r2]`.

A percent character before an operand indicates that it's a register. As an example, `%sp`, `%itp`, and `%r39` are all registers.

If a number begins with `0x` or ends with `h`, it is to be treated as a hexadecimal number. If a number begins with `b`, it is to be treated as a binary number.

Suffixes to an instruction are denoted with a `-` immediately after the opcode mnemonic, followed by the suffix itself.

### 0x00: nop (no operation)
Opcode: `000000`

Instruction-specific bitfield use?: No

Function: Does exactly nothing

Modifies flags?: No
### 0x01: add (addition)
Opcode: `000001`

Instruction-specific bitfield use?: Yes, for instruction suffixes

Function: Adds values from two registers and stores it in the `src` operand register if two registers are provided as operands. Otherwise, if one register and one immediate value is provided, the result will be stored in the register provided.

Modifies flags?: Only with `-s` suffix

The `-s` suffix is specified as `01` in the instruction-specific portion of the control word.
### 0x02: addi (signed addition)
Opcode: `000010`

Instruction-specific bitfield use?: Yes, for instruction suffixes

Function: Adds two signed values from two registers and stores it in the `src` operand register if two registers are provided as operands. Otherwise, if one register and one immediate value is provided, the result will be stored in the register provided.

Modifies flags?: Only with `-s` suffix

The `-s` suffix is specified as `01` in the instruction-specific portion of the control word.
### 0x03: mul (multiply)
Opcode: `000011`

Instruction-specific bitfield use?: Yes, for instruction suffixes

Function: Multiplies values from two registers and stores it in the `src` operand register if two registers are provided as operands. Otherwise, if one register and one immediate value is provided, the result will be stored in the register provided.

Modifies flags?: Only with `-s` suffix

The `-s` suffix is specified as `01` in the instruction-specific portion of the control word.
### 0x04: imul (signed multiply)
Opcode: `000100`

Instruction-specific bitfield use?: Yes, for instruction suffixes

Function: Multiplies signed values from two registers and stores it in the `src` operand register if two registers are provided as operands. Otherwise, if one register and one immediate value is provided, the result will be stored in the register provided.

Modifies flags?: Only with `-s` suffix

The `-s` suffix is specified as `01` in the instruction-specific portion of the control word.
### 0x05: div (division)
Opcode: `000101`

Instruction-specific bitfield use?: Yes, for instruction suffixes

Function: Divides the `src` operand by the `tgt` operand, and stores it in the `src` operand register (if two registers are provided as operands). If one register and one immediate is provided, the result will be stored in the register.

Modifies flags?: Only with `-s` suffix

The `-s` suffix is specified as `01` in the instruction-specific portion of the control word.
### 0x06: idiv (signed division)
Opcode: `000110`

Instruction-specific bitfield use?: Yes, for instruction suffixes

Function: Divides (signed) the `src` operand by the `tgt` operand, and stores it in the `src` operand register (if two registers are provided as operands). If one register and one immediate is provided, the result will be stored in the register.

Modifies flags?: Only with `-s` suffix

The `-s` suffix is specified as `01` in the instruction-specific portion of the control word.
### 0x07: cmp (compare)
Opcode: `000111`

Instruction-specific bitfield use?: No

Function: Compares the operands provided. If they are the same, the zero flag bit will be set in `%scr`.
If the `tgt` operand is higher than the `src` operand, the carry flag bit will be set in `%scr`. Otherwise, the carry flag bit will not be set.

Modifies flags?: Always
### 0x08: icmp (signed compare)
Opcode: `001000`

Instruction-specific bitfield use?: No

Function: Compares the operands provided. If they are the same (signed value), the zero flag bit will be set in `%scr`.
If the `tgt` operand is higher than the `src` operand, the carry flag bit will be set in `%scr`. Otherwise, the carry flag bit will not be set.

Modifies flags?: Always
### 0x09: bts (bit set)
Opcode: `001001`

Instruction-specific bitfield use?: No

Function: Sets a bit in the `tgt` operand. (must be a register) The value stored in the `src` operand will be used as the bit to set.

Modifies flags?: No
### 0x0A: btc (bit clear)
Opcode: `001010`

Instruction-specific bitfield use?: No

Function: Clears a bit in the `tgt` operand. (must be a register) The value stored in the `src` operand will be used as the bit to clear.

Modifies flags?: No
### 0x0B: btt (test if bit set)
Opcode: `001011`

Instruction-specific bitfield use: No

Function: Tests a bit in the `tgt` operand, which must be a register. The value stored in `src` is used as the bit to clear. If the bit tested is, in fact, set, then the zero flag bit in `%scr` will be set. Otherwise, it will be cleared.

Modifies flags?: Yes
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
### 0x17: hlt (halt CPU)
Opcode: `010111` (PRIVILEGED INSTRUCTION)

Instruction-specific bitfield use?: No

Function: Adds values from two registers and stores it in the `src` operand register if two registers are provided as operands. Otherwise, if one register and one immediate value is provided, the result will be stored in the register provided.

Modifies flags?: No
### 0x18: ret (return from subroutine)
### 0x19: iret (return from interrupt)
Opcode: `000000` (PRIVILEGED INSTRUCTION)
### 0x1A: ite (enable interrupt bit)
Opcode: `011010` (PRIVILEGED INSTRUCTION)

Instruction-specific bitfield use?: No

Function: Enables CPU interrupts by setting the Interrupt Enable flag bit in `%scr`.

Modifies flags?: No
### 0x1B: itd (disable interrupt bit)
Opcode: `011011` (PRIVILEGED INSTRUCTION)

Instruction-specific bitfield use?: No

Function: Disables CPU interrupts by clearing the Interrupt Enable flag bit in `%scr`.

Modifies flags?: No
### 0x1C: spl (set CPU privilege level)
Opcode: `011100` (PRIVILEGED INSTRUCTION)

Instruction-specific bitfield use?: No

Function: Sets the CPU privilege level. If `src` contains a value other than zero, the CPU privilege level will be set to User.
### 0x1D: litp (load %itp)
Opcode: `011101` (PRIVILEGED INSTRUCTION)

Instruction-specific bitfield use?: No

Function: Sets `%itp` to the value stored in the `src` operand.

Modifies flags?: No
### 0x1E: lmtp (load %mtp, configure MAT)
Opcode: `011110` (PRIVILEGED INSTRUCTION)

Instruction-specific bitfield use?: Yes
bits|granularity|bitmap size
---|---
`00`|MAT disabled|MAT disabled
`01`|4KB/entry|1MB bitmap
`10`|16KB/entry|256KB bitmap
`11`|64KB/entry|64KB bitmap

Function: Configures/enables/disables the Memory Access Table (MAT). The MAT controls the privilege needed to read from memory in different regions.
This is configured with a bitmap, whose pointer is stored in `%mtp`. One bit in the bitmap is an entry, which determines the privilege level for a certain-sized block of memory corresponding to the bit.
The size (e.g., granularity) of these memory blocks (and therefore, the size of the bitmap) is configured in the Instruction-Specific bitfield in the LMTP instruction's control word.
Only one mode can be set at a single time, and the MAT granularity covers the entire address space of the computer, whether or not that much memory is actually installed.

Modifies Flags?: No
### 0x1F: debug (debug instruction)
### 0x20: push (push to stack)
### 0x21: pop (pop from stack)
### 0x22: in (get dword from i/o port)
### 0x23: out (send dword to i/o port)
### 0x24: ror (bitwise rotate right)
### 0x25: rol (bitwise rotate left)
### 0x26: and (bitwise AND)
### 0x27: not (bitwise NOT)
### 0x28: or (bitwise OR)
### 0x29: xor (bitwise XOR)
### 0x2A: sub (subtract)
### 0x2B: isub (signed subtract)
### 0x2C: jmp (jump)
### 0x2D: rjmp (relative jump)
### 0x2E: rlac (calculate absolute address from relative address)
### 0x2F: call (call subroutine)
Opcode: `101111`

Instruction-specific bitfield use?: No

Function: Calls a subroutine, with the address stored in the `src` operand. The value of `%pc + 4` (i.e., the instruction directly after) is pushed on the stack.
### 0x30: rcall (relative call)
Opcode: `110000`

Instruction-specific bitfield use?: No

Function: Calls a subroutine located at a (signed) relative address stored in the `src` operand. The return address (`%pc + 4`) is pushed on the stack.

Modifies flags?: No
### 0x31: rsvd (Reserved instruction)
Opcode: `110001`

Instruction-specific bitfield use?: n/a

Function: Not yet defined - this instruction does not have any specific function and will cause an error if executed.

Modifies flags?: n/a