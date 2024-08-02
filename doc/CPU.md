# CPU architecture
`doubleword` is a 32-bit RISC CPU architecture, designed to be simple enough to be understood by one person. `doubleword` utilizes a load-store architecture, meaning that before any sort of data can be operated on, it must be loaded into the register file.
Peripherals are typically accessed through port-mapped I/O. Details on this can be found in `IO.md`.
Memory values are stored in little-endian byte order. (also: as such, the stack grows "down" in memory)
(note to self: endianness is only for memory, so remember to swap bytes in the emulator when loading/storing values to/from registers)

# instruction decoding
`doubleword` instructions are fixed-length, at 32 bits. Instructions should be aligned to 4-byte boundaries. Otherwise, an exception will occur.
A typical instruction is laid out as follows:
placeholder|placeholder
---|---
placeholder|placeholder

# registers
register|details
---|---
`%r0`|zero constant
`%r1`|general purpose
`%r2`|general purpose
`%r3`|general purpose
`%r4`|general purpose
`%r5`|general purpose
`%r6`|general purpose
`%r7`|general purpose
`%sp`|stack pointer
`%ip`|instruction pointer
`%itp`|interrupt vector table pointer
`%scr`|system control register

# %r0 - %r7
`%r1`, `%r2`, `%r3`, `%r4`, `%r5`, `%r6`, and `%r7` are all general-purpose registers available to use. Some operations may store results in these registers.
`%r0` is a constant register that ignores all writes. In case you couldn't tell, it's stuck at zero.

# %sp
`%sp` is used to store the current stack pointer. Return addresses during subroutine calls will be pushed here. Additionally, programs can put data onto the stack to save them.
(note to self: be especially careful to POP every PUSH, lest ye clobber the return addresses)
(setting up the stack involves MOV'ing a new memory address into this register.)

# %ip
`%ip` stores the memory address of the next instruction to be executed.
As doubleword uses 32-bit fixed-length instructions, `%ip` is incremented by 4 after fetching an instruction.

# %itp
`%itp` stores a pointer to the beginning of the IVT. (Interrupt Vector Table)
Modifying this register requires the CPU to be in Supervisor mode. Attempting to modify this register while in User mode results in a Privilege Exception.
The IVT is a section of memory containing pointers to different interrupt handlers.

# %scr
`%scr` is the System Control Register, and contains various bits of information relevant to the state of the CPU. `%scr` is a privileged register, meaning that attempting to read or write to it while in User mode will result in a Privilege Exception.

# exceptions & interrupts
All interrupt vectors not used here are general-purpose.

## exceptions
All CPU exceptions are processed as interrupts. 8 out of the 256 possible interrupt vectors are dedicated to exception handling.
exception|interrupt vector
---|---
Divide By Zero|`0x0`
Machine Error|`0x1`
Breakpoint|`0x2`
Handler Fault|`0x3`
Privilege Fault|`0x4`
Reserved|`0x5`
Alignment Fault|`0x6`
Invalid Opcode|`0x7`

### 0x0: divide by zero
The Divide By Zero exception occurs when a `DIV` or `IDIV` instruction is encountered that attempts to divide by zero.
### 0x1: machine error
The Machine Error exception occurs when some sort of external hardware error occurs. (for example, your 5400 RPM hard drive being set to 11,000 RPM and exploding, or perhaps you turn the monitor on and off 20 times a second)
### 0x2: breakpoint
A Breakpoint exception occurs when the `BREAK` instruction is executed. Upon a breakpoint, the CPU dumps its registers and debug information over the debug serial port. (note to self: add other things?)
### 0x3: handler fault
A Handler Fault occurs if an exception occurs while attempting to handle another exception - or if an exception goes unhandled.
### 0x4: privilege fault
If code is executed that attempts to access privileged resources while in User mode, a Privilege Fault will occur. Examples of privileged resources include system control registers like `%scr` or `%itp`, or privileged instructions such as `HLT`, `IN` or `OUT`, or `IRET`.
### 0x5: reserved
Might add memory management in the future. (or maybe never) For now, this should never come up.
### 0x6: alignment fault
When the CPU attempts to load an instruction not aligned to 4 bytes, an Alignment Fault occurs. It's usually indicative of some weird memory errors.
### 0x7: invalid opcode
An Invalid Opcode exception occurs when the CPU attempts to execute an instruction that doesn't exist. Additionally, if invalid control values are set, or invalid operands are included, those would also constitute an Invalid Opcode exception.


## interrupts
These are standardized interrupts used by system peripherals. See `IO.md` for more details.
interrupt type|interrupt vector
---|---
reserved|`0xFA`
vsync|`0xFB`
mouse|`0xFC`
keyboard|`0xFD`
hard disk|`0xFE`
timer (PIT)|`0xFF`

## the Interrupt Vector Table (IVT)
The IVT is a collection of 256 pointers to interrupt handlers. Each memory address is 32 bits wide, so the IVT is 1024 bytes long. The IVT can reside anywhere in memory, as the pointer to it (in `%itp`) can be modified.

# instruction set
nothing here yet
