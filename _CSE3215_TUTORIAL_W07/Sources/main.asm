;******************************************************************************
;*
;* CSE3215 Tutorial Winter 2007
;*
;*   	This is an example of an absolute assembler project file containing
;*      both runtime and assembly errors.
;*
;* main.asm
;*
;* April 05, 2006
;*
;******************************************************************************

 NOLIST
 include	"mc9s12dp256.inc"	; Register definitions.
 LIST

; export symbols
            XDEF        Entry   ; export 'Entry' symbol
            ABSENTRY    Entry   ; for absolute assembly: mark this as application entry point


MyRAMStart    EQU  $1000  ; absolute address to place my variables
MyROMStart    EQU  $3C00  ; absolute address to place my code/constant data

OUTPUT      equ  %11111111 
INPUT       equ  $00
BASETIME    equ  $3DB0
DELAY       equ  $20        

; variable/data section
            ORG MyRAMStart
            
; Insert here your data definition. 
rate       ds.b 1
bitCount   ds.b 1
direction  ds.b 1
               
; code section
        ORG MyROMStart
        
Entry:
        lds     #$1020
        movb    #OUTPUT, DDRB
        ldaa    #%10000000
        stab    PORTB           
        movb    #INPUT, DDRH        
        movb    #00, direction
        movb    #$07, bitCount
        
Loop
        movb    #DELAY, rate
        jsr     DelayLoop               
                    
CheckDirection:
        ldab    direction
        bne     Left
        
Right:
        lsr     PORTB
        bra     Return
        
Left:
        lsl     PORTB
        
Return:
        dec     bitCount
        bne     Loop
        
        ldaa    direction
        coma
        staa    direction
        movb    #$07, bitCount
        bra     Loop        


Delay:
        pshx
        psha
        pshb                   
        
        ldaa    rate
        
DelayLoop:                
        ldx     #BASETIME
        
Wait:
        dbne    x, Wait         
        deca             
        beq     DelayLoop		
        
        pulb
        pula
        pulx
        rts
        

        
