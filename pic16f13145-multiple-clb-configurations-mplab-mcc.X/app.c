/**
 *  @brief Source file for the Application module
 *
 *  @copyright (c) 2024 Microchip Technology Inc. and its subsidiaries.
 *
 *  Subject to your compliance with these terms, you may use Microchip software
 *  and any derivatives exclusively with Microchip products. You're responsible
 *  for complying with 3rd party license terms applicable to your use of 3rd
 *  party software (including open source software) that may accompany
 *  Microchip software.
 *  
 *  SOFTWARE IS "AS IS." NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY,
 *  APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF
 *  NON-INFRINGEMENT, MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 *  IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 *  INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 *  WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
 *  BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
 *  FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS
 *  RELATED TO THE SOFTWARE WILL NOT EXCEED AMOUNT OF FEES, IF ANY, YOU PAID
 *  DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 **/


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  Includes                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "app.h"
#include "mcc_generated_files/system/system.h"


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                             Macros and defines                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief The number of CLB configurations stored in memory.
 * @note This number must be updated if the number of configurations changes.
 */
#define NUMBER_OF_CONFIGS       ( 2 )

#define EDGE_NOT_DETECTED       ( false )
#define EDGE_DETECTED           ( true )

#define DEBOUCE_DELAY_MS(MS)    do { __delay_ms(MS); } while (false)

#define STATIC_INLINE           __attribute__((always_inline)) static inline


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                            Private (static) API                            //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initializes the array of configurations.
 * @return None. 
 */
STATIC_INLINE void InitializeConfigurations(void);

/**
 * @brief Sets the current configuration available in the array and cycles to
 *        the next one.
 * @return None. 
 */
STATIC_INLINE void SetCurrentConfiguration(void);

/**
 * @brief Changes the CLB configuration by disabling the CLB, configuring it and
 *        re-enabling it.
 * @param[in] startAddress The start address of the configuration to be loaded.
 * @return None. 
 */
STATIC_INLINE void ChangeConfiguration(uint16_t const startAddress);

/**
 * @brief Waits for the button to be pressed.
 * @return None. 
 */
STATIC_INLINE void WaitButton(void);

/**
 * @brief Detects the negative edge of the button press.
 * @return bool
 * @retval EDGE_NOT_DETECTED A negative edge was not detected.
 * @retval EDGE_DETECTED A negative edge was detected.
 */
STATIC_INLINE bool NegativeEdgeDetect(void);


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                        Private (static) definitions                        //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief The labels used in the bitstream files (the assembly files generated
 *        by the CLB tool) to mark the start of the configurations data in 
 *        memory.
 * @note This variables should always be declared as `extern` and non-`const`. 
 *       The linker will fail (even silently) if they are declared incorrectly.
 */
extern uint16_t start_clb_config;
extern uint16_t start_clb_config_alt;

/**
 * @brief The array of configurations' start addresses.
 */
static uint16_t configurations[NUMBER_OF_CONFIGS] = { 0 };

STATIC_INLINE void InitializeConfigurations(void)
{
    configurations[0] = (uint16_t) &start_clb_config;
    configurations[1] = (uint16_t) &start_clb_config_alt;
    
    return;
}

STATIC_INLINE void SetCurrentConfiguration(void)
{
    static uint8_t currentConfigIdx = 0;
    
    ChangeConfiguration(configurations[currentConfigIdx]);
    
    currentConfigIdx = (currentConfigIdx + 1) % NUMBER_OF_CONFIGS;
    
    return;
}

STATIC_INLINE void ChangeConfiguration(uint16_t const startAddress)
{
    CLB1_Disable();
    CLB1_Configure(startAddress);
    CLB1_Enable();
    
    return;
}

STATIC_INLINE void WaitButton(void)
{
    while (true)
    {
        while (NegativeEdgeDetect() == EDGE_NOT_DETECTED);

        DEBOUCE_DELAY_MS(10);

        if (BUTTON_GetValue() == LOW)
        {
            return;
        }
    }
}

STATIC_INLINE bool NegativeEdgeDetect(void)
{
    static bool lastState = HIGH;

    bool currentState = BUTTON_GetValue();

    if (currentState != lastState && currentState == LOW)
    {
        lastState = currentState;
        return EDGE_DETECTED;
    }
    else
    {
        lastState = currentState;
        return EDGE_NOT_DETECTED;
    }
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                             Public definitions                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

inline void Application_Run(void)
{
    SYSTEM_Initialize();
    
    InitializeConfigurations();
    
    while (true)
    {
        SetCurrentConfiguration();
        WaitButton();
    }
}