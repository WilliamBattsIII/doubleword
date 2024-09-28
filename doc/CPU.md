# CPU architecture
`doubleword` is a 32-bit reduced instruction-set CPU architecture, designed to be simple enough to be understood by one person, while remaining functional enough to run complex software.
Peripherals are typically accessed through port-mapped I/O. Details on this can be found in `IO.md`.
Memory values are stored in little-endian byte order. (also: as such, the stack grows "down" in memory)
(note to self: endianness is only for memory, so remember to swap bytes in the emulator when loading/storing values to/from registers)

# instruction decoding & instruction set
`doubleword` instructions are fixed-length, at 32 bits. Additionally, instructions should be aligned to 4-byte boundaries and memory accesses must be aligned to their size, otherwise an Alignment Fault will occur.
The first 16 bits of each instruction is a control word, indicating the operation, operand types, and other information.
### control word
bits|function
---|---
`[0:5]`|opcode
`[6:7]`|source operand type
`[8:9]`|target operand type
`[10:11]`|reserved for instruction-specific info
`[12:15]`|condition code

(table assumes bit 0 is the LSB)
### operand types
value|type|size (bit-width of value in instruction)|description
---|---|---|---
`00`|reg. ptr.|8 bits|register containing a 32-bit memory address (used in mov, store, etc)
`01`|register|8 bits|the register whose contents will be operated on
`10`|8-bit immed.|8 bits|immediate meant to hold relative addresses for load/store/IO instructions
`11`|immed. jmp ptr|16 bits|16 bit immed. value, only used in relative jump instructions

### condition types
(not done yet)
# instruction set
See `ISA.md` for a detailed instruction set.

# registers
register|details
---|---
`%r0`|zero constant
`%r1`|general purpose
`...`|general purpose
`%r63`|general purpose
`%sp`|stack pointer
`%ip`|instruction pointer
`%itp`|interrupt vector table pointer
`%mtp`|memory access table pointer
`%scr`|system control register

# %r0 - %r63
`%r1` to `%r63` are all general-purpose 32-bit registers. Some operations may store results in these registers.
`%r0` is a constant register that ignores all writes, and only reads zero.

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

# %mtp
`%mtp` stores a pointer to the beginning of the MAT. (Memory Access Table)
Modifying this register requires the CPU to be in Supervisor mode. Attempting to modify this register while in User mode results in a Privilege Exception.
The MAT is a bitmap which enables/disables memory protection for certain regions of memory.

# %scr
`%scr` is the System Control Register, and contains information relevant to the state of the CPU. `%scr` is a privileged register, meaning that attempting to read or write to it while in User mode will result in a Privilege Exception.
Some instructions may depend on the contents of this register (ex: determining if a privileged instruction can run, or conditional instructions utilizing CPU flags)
(bits in order: ALU flags, CPU privilege level, MAT granularity, interrupt enable flag, memory protection enable flag, debug flag)
(ALU flags: zero, parity, carry, overflow, sign)



# exceptions & interrupts
All interrupt vectors not included in these specifications should be assumed to be general-purpose and free to use.
## exceptions
All CPU exceptions are processed as interrupts. The first 8 out of the 256 possible interrupt vectors are dedicated to exception handling.
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
The Machine Error exception occurs when some sort of hardware error occurs. (for example, your hard drive randomly exploding, or perhaps you turn the monitor on and off 20 times a second) (lp0 on fire?)
### 0x2: breakpoint
A Breakpoint exception occurs when the `DEBUG` instruction is executed. Upon a breakpoint, the CPU dumps its registers and debug information over the debug serial port. (note to self: add other things?) (second note to self: what the hell is a breakpoint)
### 0x3: handler fault
A Handler Fault occurs if an exception occurs while attempting to handle another exception - or if an exception goes unhandled. In the event that this exception is unhandled (or an exception occurs within it), the machine will attempt to 
### 0x4: privilege fault
If code is executed that attempts to access privileged resources while in User mode, a Privilege Fault will occur. Privileged resources include control registers, memory marked as protected in the MAT, or privileged instructions.
### 0x5: reserved
Reserved exception vector.
### 0x6: alignment fault
When the CPU attempts to access memory that's not properly aligned to the width of the data, an Alignment Fault occurs.

### 0x7: invalid opcode
An Invalid Opcode exception occurs when the CPU attempts to execute an instruction that doesn't exist. Additionally, if invalid control values are set, or invalid operands are included, those would also constitute an Invalid Opcode exception.

## interrupts
These are standardized interrupts used by system peripherals. See `IO.md` for more details.
interrupt type|interrupt vector
---|---
reserved|`0xF7`
serial port|`0xF8`
reserved|`0xF9`
reserved|`0xFA`
vsync|`0xFB`
mouse|`0xFC`
keyboard|`0xFD`
hard disk|`0xFE`
timer (PIT)|`0xFF`

As the `doublebox` architecture lacks a sophisticated interrupt controller chip, specific interrupts are unable to be masked - interrupts can only be disabled or enabled. (this only applies to hardware/software interrupts - exceptions still work)
Instead, programs running on the computer must use the I/O bus to enable or disable specific devices.

### what happens when an interrupt happens?
Whether it be a software or hardware interrupt, a standard process occurs every time an interrupt is risen in the processor.

The current instruction executing is allowed to finish. After that, the `%scr` register is pushed onto the stack. (4 bytes)
Then, the return address (immediately after the last instruction, 4 bytes) is pushed to the stack.
These two values will be restored onto the stack when an `iret` is executed. No other registers should be altered. If they are, it is the responsibility of the interrupt handler to restore them before returning.


## the Interrupt Vector Table (IVT)
The IVT is a collection of 256 pointers to interrupt handlers. (basically just a jump table that uses the interrupt vector as an index)
Each handler pointer is 32 bits wide, so the IVT is 1024 bytes long. 
The IVT can reside anywhere in memory that aligns to four-byte boundaries.
Each pointer is aligned to 4-byte boundaries, so there's a new pointer every 4 bytes.

# memory protection, and the Memory Access Table (MAT)

The MAT is a designated region of memory containing a bitmap of 


# boot process
### system setup
By default, the `doubleword` emulator is set up with 32 MB of RAM. As listed in `IO.md`, peripherals are disabled via the power controller and must be initialized before use.
### firmware setup
The `doubleword` architecture has a 3-step boot process. First, a firmware program stored in ROM is loaded into memory beginning at `0x1000`. At this point, CPU execution begins. All general-purpose registers are zeroed out, in addition to `%itp`. Interrupts are disabled. The stack pointer is set to to the next 32-bit boundary below the loading point of the firmware, at `0x0FFC`, as it grows downward in memory.
### system initialization
The firmware initializes hardware and prepares the computer for the second part of the boot process.
The last thing that the system firmware does is scan for any attached hard drives marked as bootable. If multiple are found, a menu is shown which will ask the user to pick a volume. If just one is found, it will automatically be booted. If there are no bootable drives, the firmware will display an error and hang. (note to self: add more types of storage later?)
### "bootable" requirements
A drive is considered bootable if its first sector (referred to as sector zero) begins with `0xEEEE`. The rest of the drive may be used for any purpose.
### from the bootloader onwards
Continuing on, the bootloader is now in control of execution. It will load the rest of the operating system from disk, and execution will proceed from there, with the system fully booted.


# fun features of the doubleword architecture
### conditional instructions
Similar to the ARM architecture, nearly all instructions are conditional. This makes conditional things easy.
### %r0: the zero register
Similar to many RISC architectures, the zeroth register is a zero constant that ignores writes and always returns zero. This makes certain instruction encodings much simpler.
### differentiation between supervisor and user privilege
This feature is found in many modern processors and allows for development of complex operating systems.
### paging (not a feature)
Programming advanced software and operating systems for this processor would be much easier with paging and virtual memory. However, that's not a thing - since I still don't know enough about it at the moment, and I figured "keep it simple" was a good excuse. However, in the interest of practicality, a rudimentary form of memory protection has been implemented with the Memory Access Table - a designated bitmap of the privilege levels required to access specific blocks of memory.