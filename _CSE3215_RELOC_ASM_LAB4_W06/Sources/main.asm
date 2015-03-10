;******************************************************************************
;*
;* CSE3215 Relocatable Assembly Source Code Template for Lab4 Winter 2005.
;*
;* main.asm
;*
;* Jan 10, 2006
;*
;******************************************************************************

NOLIST
 include	"mc9s12dp256.inc"	; Register definitions.
LIST

; export symbols
            XDEF Entry, main, PORTK, DDRK, PORTA, DDRA
            XREF Delay5ms, LCDReset, LCDWriteMessageString
            XREF LCDWriteCommandString, Delay50us, LCDWriteChar

; variable/data section
MY_EXTENDED_RAM: SECTION
; Insert here your data definition. For demonstration, temp_byte is used.
temp_byte   ds.b     1

; code section
.init:      SECTION
             
main:
Entry:
        CLI                     ; enable interrupts
A:
	nop
	bra	A          