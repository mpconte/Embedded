;******************************************************************************
;*
;* CSE3215 Relocatable Assembly Source Code Template for the MC9S12DP256B
;* microcontroller.
;*
;* main.asm
;*
;* Dec 07, 2005
;*
;******************************************************************************

; export symbols
            XDEF Entry, main
            ; we use export 'Entry' as symbol. This allows us to
            ; reference 'Entry' either in the linker .prm file
            ; or from C/C++ later on


; variable/data section
MY_EXTENDED_RAM: SECTION
; Insert here your data definition. For demonstration, temp_byte is used.
temp_byte ds.b 1

; code section
MyCode:     SECTION
main:
Entry:
       CLI               ; enable interrupts
loop:
       MOVB #1,temp_byte ; just some demonstration code
       NOP               ; Insert here your own code

       BRA loop          ; endless loop


