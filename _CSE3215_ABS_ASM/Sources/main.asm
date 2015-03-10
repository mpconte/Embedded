;******************************************************************************
;*
;* CSE3215 Relocatable Assembly Source Code Template for the MC9S12DP256B
;* microcontroller.
;*
;* main.asm
;*
;* Jan 09, 2006
;*
;******************************************************************************

 NOLIST
 include	"mc9s12dp256.inc"	; Register definitions.
 LIST

; export symbols
            XDEF Entry        ; export 'Entry' symbol
            ABSENTRY Entry    ; for absolute assembly: mark this as application entry point


MyRAMStart    EQU  $1000  ; absolute address to place my variablesMy
MyROMStart    EQU  $2000  ; absolute address to place my code/constant data

; variable/data section
            ORG MyRAMStart
; Insert here your data definition. For demonstration, temp_byte is used.
temp_byte   ds.b 1


; code section
            ORG MyROMStart
Entry:
            CLI                ; enable interrupts

            MOVB #1,temp_byte  ; just some demonstration code
            NOP                ; Insert here you own code

            BRA Entry  ; endless loop


