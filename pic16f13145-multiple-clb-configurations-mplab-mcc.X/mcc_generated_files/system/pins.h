/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.0.0
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_RA5 aliases
#define OUTPUT_TRIS                 TRISAbits.TRISA5
#define OUTPUT_LAT                  LATAbits.LATA5
#define OUTPUT_PORT                 PORTAbits.RA5
#define OUTPUT_WPU                  WPUAbits.WPUA5
#define OUTPUT_OD                   ODCONAbits.ODCA5
#define OUTPUT_ANS                  ANSELAbits.ANSA5
#define OUTPUT_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define OUTPUT_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define OUTPUT_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define OUTPUT_GetValue()           PORTAbits.RA5
#define OUTPUT_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define OUTPUT_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define OUTPUT_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define OUTPUT_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define OUTPUT_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define OUTPUT_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define OUTPUT_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define OUTPUT_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)
// get/set IO_RC3 aliases
#define BUTTON_TRIS                 TRISCbits.TRISC3
#define BUTTON_LAT                  LATCbits.LATC3
#define BUTTON_PORT                 PORTCbits.RC3
#define BUTTON_WPU                  WPUCbits.WPUC3
#define BUTTON_OD                   ODCONCbits.ODCC3
#define BUTTON_ANS                  ANSELCbits.ANSC3
#define BUTTON_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define BUTTON_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define BUTTON_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define BUTTON_GetValue()           PORTCbits.RC3
#define BUTTON_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define BUTTON_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define BUTTON_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define BUTTON_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define BUTTON_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define BUTTON_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define BUTTON_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define BUTTON_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)
/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);


#endif // PINS_H
/**
 End of File
*/