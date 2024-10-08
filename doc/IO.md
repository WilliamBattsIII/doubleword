# documentation for the doubleword I/O bus
The I/O bus supports 256 different ports to be written to or read from.

The I/O bus is accessed via the `IN` and `OUT` instructions, which are used to read or write a 32-bit value to one of the I/O ports. Data over the bus is sent in a parallel manner - that is, all 32 bits at once. (note to self: that means, don't worry about endian-ness, just copy the value from one thing to the other in the emulator)

# 0x00: System Power Controller
offset|function
---|---
`0x0`|system shutdown register
`0x1`|error code register
`0x2`|configuration register
`0x3`|status register

### 0x00: System Shutdown Register (write-only)
Write any value to this register to power off the machine entirely. (terminates the emulator)
This register always returns zero upon reads.
### 0x01: Error Code Register (read-only)
If an error occurs in the power controller after a command has been sent via the configuration register, the error will be reported here. If there is no error, the register will read zero.
### 0x02: Configuration Register (to be implemented)
The lower 8 bits of a write to this port will be interpreted as follows:
(assuming "bit 7" is the MSB and "bit 0" is the LSB)
### [7:6]: Command
value|command
---|---
`00`|Query state of device
`01`|Power on device
`10`|Power off device
`11`|Reserved
### [5:3]: Device ID
value|id
---|---
`0`|Drive Controller
`1`|Input Controller
`2`|Graphics Controller
`3`|Serial Port
`everything else`|Reserved
### [2:0]: Reserved
(note: maybe use for device-specific functions?)
#### 0x03: Output Register (read-only)
The contents of this register will change depending on the status of the device configured, as well as the type of command sent.
Refer to the below table for a list of statuses.

value|status
---|---
`0x0`|Operation completed successfully
`0x1`|Operation in progress
`0x2`|Error Occurred
`0x3`|Device is on
`0x4`|Device is off
# 0x70: Drive Controller (to be implemented)
This peripheral is powered off upon machine start, and needs to be powered on via the System Power Controller.
(placeholder)

# 0x80: Programmable Interrupt Timer (PIT) (to be implemented)

# 0xD0: Input Controller
This peripheral is powered off upon machine start, and needs to be powered on via the System Power Controller.
### 0xD0: Configuration Register
The Configuration Register can be used to enable or disable different subsystems of the Input Controller.
The Configuration Register operates as follows:
bits|function
---|---
`[31:2]`|reserved
`[1]`|if high, mouse enabled, otherwise disabled
`[0]`|if high, keyboard enabled, otherwise disabled

(table assumes bit 0 is the LSB)
### 0xD1: Keyboard
bits|function
---|---
`[31:9]`|reserved
`[8:1]`|IBM PC keyboard scancode
`[0]`|if high, key pressed - if low, key released

(table assumes bit 0 is the LSB)
### 0xD2: Mouse
bits|function
---|---
placeholder|placeholder

(table assumes bit 0 is the LSB)

# 0xE0: Graphics Controller
This peripheral is powered off upon machine start, and needs to be powered on via the System Power Controller.

# 0xF0: RTC (To be implemented)
The RTC can be written to, in the event that the time or date must be changed.
Ideally, software should temporarily pause the RTC before writing to it.
### 0xF0: Time/Date Register (HIGH)
bits|function
---|---
placeholder|placeholder

(table assumes bit 0 is the LSB)
### 0xF1: Time/Date Register (LOW)
bits|function
---|---
placeholder|placeholder

(table assumes bit 0 is the LSB)
### 0xF2: Pause/Resume RTC
Writing a one to this register resumes the RTC.
Writing a zero to this register pauses the RTC.

# 0xFE: Debug Port
### 0xFE: Debug Serial Port (IN)
If a byte is available over the serial port, a read will get it from this register. Otherwise, this register will hold zero.
### 0xFF: Debug Serial Port (OUT)
The lowest 8 bits of a write to this register are output as a byte on the "serial" output. (stdout)
This peripheral is powered off upon machine start, and needs to be powered on via the System Power Controller.