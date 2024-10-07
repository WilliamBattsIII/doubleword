# doubleword assembly info:
## ordering
Examples:

`add %r1, %r2`

`ldw %r1, [%r2]`

`push program_label`

`jmp program_label`

`jmp [%r17]`

`add a, b`

In `doubleword` assembly, the opcode mnemonic comes first in the instruction, and is followed by operands.

The A operand comes before the B operand. These may be followed by certain values, such as with immediates, or modifiers.

The target operand is usually the location where the result of the instruction will be stored. This differs if the target operand is not a register, or if alternate behavior is specified.
## assembler conventions
There are various indicators and conventions within the `doubleword` assembly language, mainly used to make writing the assembler easier.

Brackets around a label or register signify that the value is a pointer.
For example, say `%r2` is a register containing a memory address, and the memory at that address contains the character `A`. If you wanted to load `%r1` with the contents of the memory address in `%r2,` you could dereference the pointer with `ldb %r1, [%r2]`.

A percent character before an operand indicates that it's a register. As an example, `%sp`, `%itp`, and `%r39` are all registers.

If a number begins with `0x` or ends with `h`, it is to be treated as a hexadecimal number. If a number begins with `b`, it is to be treated as a binary number.

Suffixes to an instruction are denoted with a `-` immediately after the opcode mnemonic, followed by the suffix itself.

## load-store architecture
As with most RISC/RISC-like architectures, data operations can only be performed on values in the register file.
Immediates aren't really a thing, save for a few instructions - it should be assumed below that all operands are registers.

## note about jmp/rjmp
If you jump to a location that can fit in a relative jump immediate (16 bits, so +/- ~32K from current IP), the assembler may optimize the jump into a relative jump. This may explain discrepancies in decompiliations of programs

# doubleword ISA

### 0x00: nop (no operation)
Opcode: `000000`

Instruction-specific bitfield use?: No

Operands: None

Function: Does exactly nothing.

Modifies flags?: No
### 0x01: add (addition)
Opcode: `000001`

Instruction-specific bitfield use?: Yes, for instruction suffixes

Operands: A, B

Function: Adds values from the two registers and stores it in the `b` operand register.

Modifies flags?: Only with `-s` suffix

The `-s` suffix is specified as `01` in the instruction-specific portion of the control word.
### 0x02: addi (signed addition)
Opcode: `000010`

Instruction-specific bitfield use?: Yes, for instruction suffixes

Operands: A, B

Function: Adds two signed values from two registers and stores it in the `b` operand register.

Modifies flags?: Only with `-s` suffix

The `-s` suffix is specified as `01` in the instruction-specific portion of the control word.
### 0x03: mul (multiply)
Opcode: `000011`

Instruction-specific bitfield use?: Yes, for instruction suffixes

Operands: A, B

Function: Multiplies values from two registers and stores it in the `b` operand register.

Modifies flags?: Only with `-s` suffix

The `-s` suffix is specified as `01` in the instruction-specific portion of the control word.
### 0x04: imul (signed multiply)
Opcode: `000100`

Instruction-specific bitfield use?: Yes, for instruction suffixes

Operands: A, B

Function: Multiplies signed values from two registers and stores it in the `b` operand register.

Modifies flags?: Only with `-s` suffix

The `-s` suffix is specified as `01` in the instruction-specific portion of the control word.
### 0x05: div (division)
Opcode: `000101`

Instruction-specific bitfield use?: Yes, for instruction suffixes

Operands: A, B

Function: Divides the `b` operand by the `a` operand, and stores it in the `b` operand register.
Modifies flags?: Only with `-s` suffix

The `-s` suffix is specified as `01` in the instruction-specific portion of the control word.
### 0x06: idiv (signed division)
Opcode: `000110`

Instruction-specific bitfield use?: Yes, for instruction suffixes

Operands: A, B

Function: Divides (signed) the `b` operand by the `a` operand, and stores it in the `b` operand register.

Modifies flags?: Only with `-s` suffix

The `-s` suffix is specified as `01` in the instruction-specific portion of the control word.
### 0x07: cmp (compare)
Opcode: `000111`

Instruction-specific bitfield use?: No

Operands: A, B

Function: Compares the operands provided. If they are the same, the zero flag bit will be set in `%scr`.
If the `a` operand is higher than the `b` operand, the carry flag bit will be set in `%scr`. Otherwise, the carry flag bit will not be set.

Modifies flags?: Always
### 0x08: icmp (signed compare)
Opcode: `001000`

Instruction-specific bitfield use?: No

Operands: A, B

Function: Compares the operands provided. If they are the same (signed value), the zero flag bit will be set in `%scr`.
If the `a` operand is higher than the `b` operand, the carry flag bit will be set in `%scr`. Otherwise, the carry flag bit will not be set.

Modifies flags?: Always
### 0x09: bts (bit set)
Opcode: `001001`

Instruction-specific bitfield use?: No

Operands: A, B

Function: Sets a bit in the `a` operand. The value stored in the `b` operand will be used as the bit to set.

Modifies flags?: No
### 0x0A: btc (bit clear)
Opcode: `001010`

Instruction-specific bitfield use?: No

Operands: A, B

Function: Clears a bit in the `a` operand. The value stored in the `b` operand will be used as the bit to clear.

Modifies flags?: No
### 0x0B: btt (test if bit set)
Opcode: `001011`

Instruction-specific bitfield use: No

Operands: A, B

Function: Tests a bit in the `a` operand, which must be a register. The value stored in `b` is used as the bit to test. If the bit tested is, in fact, set, then the zero flag bit in `%scr` will be set. Otherwise, it will be cleared.

Modifies flags?: Always
### 0x0C: sla (bitshift left)
Opcode: `001100`

Instruction-specific bitfield use: Yes, only for instruction suffixes

Operands: A, B

Function: Shifts the `b` operand (a register) left by (value specified in `a` operand) bits.

Modifies flags?: Only with `-s` suffix
### 0x0D: sra (shift right arithmetic)
Opcode: `001101`

Instruction-specific bitfield use: Yes, only for instruction suffixes

Operands: A, B

Function: Shifts the `b` operand (a register) right by (value specified in `a` operand) bits. Sign-extension is applied.
This means that the sign is preserved in the MSB, rather than filling empty space with zeroes.


Modifies flags?: Only with `-s` suffix
### 0x0E: srl (shift right logical)
Opcode: `001110`

Instruction-specific bitfield use: Yes, only for instruction suffixes

Operands: A, B

Function: Shifts the `b` operand (a register) right by (value specified in `a` operand) bits.
Logical shifting simply means that the empty space from a bitwise right shift is filled with zeroes.

Modifies flags?: Only with `-s` suffix
### 0x0F: inc (increment)
Opcode: `001111`

Instruction-specific bitfield use: Yes, only for instruction suffixes

Operands: A

Function: Increments the operand provided (only takes one operand) by one.

Modifies flags?: Only with `-s` suffix
### 0x10: dec (decrement)
Opcode: `010000`

Instruction-specific bitfield use: Yes, only for instruction suffixes

Operands: A

Function: Only takes one operand. Decrements the operand by one.

Modifies flags?: Only with `-s` suffix
### 0x11: ldb (load byte)
Opcode: `010001`

Instruction-specific bitfield use: Yes

bits|load type
---|---
`00`|load immediate
`01`|load direct (relative addressing)
`10`|load indirect (relative addressing)
`11`|reserved

Operands: A, B

Function:

Modifies flags?: No
### 0x12: lbw (load word)
Opcode: `010010`

Instruction-specific bitfield use: Yes

bits|load type
---|---
`00`|load immediate
`01`|load direct (relative addressing)
`10`|load indirect (relative addressing)
`11`|reserved

Operands: A, B

Function:

Modifies flags?: No
### 0x13: ldd (load dword)
Opcode: `010011`

Instruction-specific bitfield use: Yes

bits|load type
---|---
`00`|load immediate
`01`|load direct (relative addressing)
`10`|load indirect (relative addressing)
`11`|reserved

Operands: A, B

Function:

Modifies flags?: No
### 0x14: stb (store byte)
Opcode: `010100`

Instruction-specific bitfield use: Yes

Operands: A, B

Function:

Modifies flags?: No
### 0x15: stw (store word)
Opcode: `010101`

Instruction-specific bitfield use: Yes

Operands: A, B

Function:

Modifies flags?: No
### 0x16: std (store dword)
Opcode: `010110`

Instruction-specific bitfield use: Yes

Operands: A, B

Function: 

Modifies flags?: No
### 0x17: hlt (halt CPU)
Opcode: `010111` (PRIVILEGED INSTRUCTION)

Instruction-specific bitfield use?: No

Operands: None

Function: Stops execution until the next CPU interrupt.

Modifies flags?: No
### 0x18: ret (return from subroutine)
Opcode: `011000`

Instruction-specific bitfield use?: No

Operands: None

Function:

Modifies flags?: No
### 0x19: iret (return from interrupt)
Opcode: `011001` (PRIVILEGED INSTRUCTION)

Instruction-specific bitfield use: No

Operands: None

Function: Returns control from a CPU interrupt back to the previously-running code.
This is accomplished by popping the return address and restoring it, then popping the old `%scr` value off the stack and restoring it.

Modifies flags?: No
### 0x1A: ite (enable interrupt bit)
Opcode: `011010` (PRIVILEGED INSTRUCTION)

Instruction-specific bitfield use?: No

Operands: None

Function: Enables CPU interrupts by setting the Interrupt Enable flag bit in `%scr`.

Modifies flags?: No
### 0x1B: itd (disable interrupt bit)
Opcode: `011011` (PRIVILEGED INSTRUCTION)

Instruction-specific bitfield use?: No

Operands: None

Function: Disables CPU interrupts by clearing the Interrupt Enable flag bit in `%scr`.

Modifies flags?: No
### 0x1C: spl (set CPU privilege level)
Opcode: `011100` (PRIVILEGED INSTRUCTION)

Instruction-specific bitfield use?: No

Operands: A

Function: Sets the CPU privilege level. If `a` contains a value other than zero, the CPU privilege level will be set to User.
### 0x1D: litp (load %itp)
Opcode: `011101` (PRIVILEGED INSTRUCTION)

Instruction-specific bitfield use?: No

Operands: A

Function: Sets `%itp` to the value stored in the `a` operand.

Modifies flags?: No
### 0x1E: lmtp (load %mtp, configure MAT)
Opcode: `011110` (PRIVILEGED INSTRUCTION)

Instruction-specific bitfield use?: Yes

bits|granularity|bitmap size
---|---|---
`00`|MAT disabled|MAT disabled
`01`|4KB/entry|1MB bitmap
`10`|16KB/entry|256KB bitmap
`11`|64KB/entry|64KB bitmap

Operands: A

Function: Configures/enables/disables the Memory Access Table (MAT). The MAT controls the privilege needed to read from memory in different regions.
The pointer to the MAT is stored in the `a` operand, and should be a 32-bit absolute address.
This is configured with a bitmap, whose pointer is stored in `%mtp`. One bit in the bitmap is an entry, which determines the privilege level for a certain-sized block of memory corresponding to the bit.

The size (e.g., granularity) of these memory blocks (and therefore, the size of the bitmap) is configured in the Instruction-Specific bitfield in the LMTP instruction's control word.

Only one mode can be set at a single time, and the MAT granularity covers the entire address space of the computer, whether or not that much memory is actually installed.

Modifies Flags?: No
### 0x1F: debug (debug instruction)
Opcode: `011111`
### 0x20: push (push to stack)
Opcode: `100000`
### 0x21: pop (pop from stack)
Opcode: `100001`
### 0x22: in (get dword from i/o port)
Opcode: `100010`
### 0x23: out (send dword to i/o port)
Opcode: `100011`
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

Operands: A

Function: Calls a subroutine, with the address stored in the `a` operand.
The value of `%pc + 4` (i.e., the instruction directly after) is pushed on the stack. After this, the CPU jumps to the address specified.
### 0x30: rcall (relative call)
Opcode: `110000`

Instruction-specific bitfield use?: No

Operands: A

Function: Calls a subroutine located at a (signed) relative address stored in the `a` operand.
The return address (`%pc + 4`) is pushed on the stack. After this, the CPU jumps to the address specified.

Modifies flags?: No
### 0x31: rsvd (Reserved instruction)
Opcode: `110001`

Instruction-specific bitfield use?: n/a

Operands: n/a

Function: Not yet defined - this instruction does not have any specific function and will cause an error if executed.

Modifies flags?: n/a
