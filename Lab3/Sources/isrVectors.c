/******************************************************************************

 York University COSC3215
 isrVectors.c
 June 12, 2004 

********************************************************************************/

/*******************************************************************************
 External ISR Function prototypes
********************************************************************************/
__interrupt void button_press(void);
__interrupt void ms_delay(void);


/******************************************************************************
 Type definitions
*******************************************************************************/
typedef void (*IsrFunc)(void);                       /* ISR function type     */


/******************************************************************************
 Global constants
 
 Note: Set the isr base address as follows:
        0x3E00 for the D-Bug12 Monitor target
        0xFF80 when Simulating 
*******************************************************************************/
const IsrFunc _vectab[] @0x3e00 /*@0xFF80*/ =
{
  (IsrFunc)0,                                        /* Reserved 0xFF80               */
  (IsrFunc)0,                                        /* Reserved 0xFF82               */
  (IsrFunc)0,                                        /* Reserved 0xFF84               */
  (IsrFunc)0,                                        /* Reserved 0xFF86               */
  (IsrFunc)0,                                        /* Reserved 0xFF88               */
  (IsrFunc)0,                                        /* Reserved 0xFF8A               */
  (IsrFunc)0,                                        /* PWM Emergency Shutdown 0xFF8C */
  (IsrFunc)0,                                        /* PortP Interrupt 0xFF8E        */
  (IsrFunc)0,                                        /* MSCAN4 Transmit 0xFF90        */
  (IsrFunc)0,                                        /* MSCAN4 Receive 0xFF92         */
  (IsrFunc)0,                                        /* MSCAN4 Errors 0xFF94          */
  (IsrFunc)0,                                        /* MSCAN4 WakeUp 0xFF96          */
  (IsrFunc)0,                                        /* MSCAN3 Transmit 0xFF98        */
  (IsrFunc)0,                                        /* MSCAN3 Receive 0xFF9A         */
  (IsrFunc)0,                                        /* MSCAN3 Errors 0xFF9C          */
  (IsrFunc)0,                                        /* MSCAN3 WakeUp 0xFF9E          */
  (IsrFunc)0,                                        /* MSCAN2 Transmit 0xFFA0        */
  (IsrFunc)0,                                        /* MSCAN2 Receive 0xFFA2         */
  (IsrFunc)0,                                        /* MSCAN2 Errors 0xFFA4          */
  (IsrFunc)0,                                        /* MSCAN2 WakeUp 0xFFA6          */
  (IsrFunc)0,                                        /* MSCAN1 Transmit 0xFFA8        */
  (IsrFunc)0,                                        /* MSCAN1 Receive 0xFFAA         */
  (IsrFunc)0,                                        /* MSCAN1 Errors 0xFFAC          */
  (IsrFunc)0,                                        /* MSCAN1 WakeUp 0xFFAE          */
  (IsrFunc)0,                                        /* MSCAN0 Transmit 0xFFB0        */
  (IsrFunc)0,                                        /* MSCAN0 Receive 0xFFB2         */
  (IsrFunc)0,                                        /* MSCAN0 Errors 0xFFB4          */
  (IsrFunc)0,                                        /* MSCAN0 WakeUp 0xFFB6          */
  (IsrFunc)0,                                        /* Flash 0xFFB8                  */
  (IsrFunc)0,                                        /* Eeprom WakeUp 0xFFBA          */
  (IsrFunc)0,                                        /* SPI2  0xFFBC                  */
  (IsrFunc)0,                                        /* SPI1  0xFFBE                  */
  (IsrFunc)0,                                        /* IIC Bus 0xFFC0                */
  (IsrFunc)0,                                        /* DLC 0xFFC2                    */
  (IsrFunc)0,                                        /* SCME 0xFFC4                   */
  (IsrFunc)0,                                        /* CRG Lock 0xFFC6               */
  (IsrFunc)0,                                        /* Pulse AccB Overflow 0xFFC8    */
  (IsrFunc)0,                                        /* Mod Down Cnt Underflow 0xFFCA */
  (IsrFunc)button_press,                             /* PortH Interrupt 0xFFCC        */
  (IsrFunc)0,                                        /* PortJ Interrupt 0xFFCE        */
  (IsrFunc)0,                                        /* ATD1 0xFFD0                   */
  (IsrFunc)0,                                        /* ATD0 0xFFD2                   */
  (IsrFunc)0,                                        /* SCI1 0xFFD4                   */
  (IsrFunc)0,                                        /* SCI0 0xFFD6                   */
  (IsrFunc)0,                                        /* SPI0 0xFFD8                   */
  (IsrFunc)0,                                        /* Pulse AccA Input Edge 0xFFDA  */
  (IsrFunc)0,                                        /* Pulse AccA Overflow 0xFFDC    */
  (IsrFunc)0,                                 /* Timer Overflow 0xFFDE         */
  (IsrFunc)ms_delay,                                        /* Timer 7 0xFFE0                */ 
  (IsrFunc)0,                                        /* Timer 6 0xFFE2                */
  (IsrFunc)0,                                        /* Timer 5 0xFFE4                */
  (IsrFunc)0,                                        /* Timer 4 0xFFE6                */
  (IsrFunc)0,                                        /* Timer 3 0xFFE8                */
  (IsrFunc)0,                                        /* Timer 2 0xFFEA                */
  (IsrFunc)0,                                        /* Timer 1 0xFFEC                */
  (IsrFunc)0,                                   /* Timer 0 0xFFEE                */
  (IsrFunc)0,                                        /* RTI 0xFFF0                    */
  (IsrFunc)0,                                        /* IRQ 0xFFF2                    */
  (IsrFunc)0,                                        /* XIRQ 0xFFF4                   */
  (IsrFunc)0,                                        /* SWI 0xFFF6                    */
  (IsrFunc)0,                                        /* Unimpl Instr Trap 0xFFF8      */
  (IsrFunc)0,                                        /* COP Failure Reset(N/A) 0xFFFA */
  (IsrFunc)0,                                        /* COP Clk Mon Fail(N/A) 0xFFFC  */
  (IsrFunc)0                                         /* Reset(N/A) 0xFFFE             */
};


// isrVectors.c
