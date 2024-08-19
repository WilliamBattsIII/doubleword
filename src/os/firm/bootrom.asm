ifc ;disable interrupts

out 00h, 40h ;01000000 enable disk controller
out 00h, 58h ;01011000 enable debug serial

;debug_serial_print
;arguments: %r17 (pointer to ASCIIZ string)
;(clobbers %r17)
debug_serial_print:
    outb ffh, %r17
    ; note to self: this code is wrong, need to find what %r17 points to
    cmp %r17, 00h 
    ifz jmp debug_serial_error
    dec %r17 ;(little endian)
    ret