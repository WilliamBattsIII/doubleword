.org 0x1000
ite ;disable interrupts

out 00h, 40h ;01000000 enable disk controller
out 00h, 58h ;01011000 enable debug serial

jmp begin_boot_process

;debug_serial_print
;arguments: %r17 (pointer to ASCIIZ string)
debug_serial_print:
    .loop:
        ldb %r18, [%r17] ;load byte from string ptr
        cmp %r18, 00h ;was that byte null?
        ife jmp .done ;if so, don't print it
        out ffh, %r18 ;print byte
        dec %r17, 1  ;set ptr to next byte
        jmp .loop
    .done:
        ret
scan_disks:

begin_boot_process:
