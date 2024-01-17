<a href="https://www.microchip.com">
    <picture>
        <source media="(prefers-color-scheme: light)" srcset="images/microchip-light.png">
        <source media="(prefers-color-scheme: dark)" srcset="images/microchip-dark.png">
        <img alt="Microchip logo" src="images/microchip-light.png">
    </picture>
</a>

# Getting Started with Multiple Configurations for the Configurable Logic Block (CLB) - Use Case for the PIC16F13145 Microcontroller with MCC Melody

The PIC16F13145 device family of microcontrollers is equipped with a complex programmable logic device peripheral. The Configurable Logic Block (CLB) is a collection of logic elements that can be programmed to perform a wide variety of digital logic functions. The logic function may be completely combinatorial, sequential, or a combination of the two, enabling users to incorporate hardware-based custom logic into their applications. This peripheral presents an unique way of modifying its control registers and setting up the logic elements. The CLB module consists of two sets of register interfaces: the standard Special Function Register (SFR) interface, and a Configuration Interface. These SFRs allow user software the ability to enable/disable the module, program input bits into the CLB memory, select a clock source, read the outputs of each Basic Logic Element (BLE), and enable Peripheral Pin Select (PPS) outputs for specific BLE outputs. The CLB’s logic elements cannot be configured using the SFR interface and consequently the Configuration Interface must be used for a complete configuration of the module. The Configuration Interface does not appear as an SFR in the Register Map and is not directly user-accessible. Instead, the Configuration Interface is accessed through the Nonvolatile Memory Control (NVM) Scanner module. Therefore, the configuration values for the logic elements, also called the bitstream, must reside in Program Flash Memory (PFM) and the NVM Scanner transfers the information from the PFM into the CLB registers. Storing the bitstream in the Program Flash Memory offers extensive flexibility for a wide range of applications due to the fact that one can store multiple bitstreams in memory which can be loaded into the CLB registers at runtime. This code example will explore this concept and will present a use case which changes the bitstream of two simple digital designs during runtime with the press of a button.

## Related Documentation

- [PIC16F13145 Product Family](https://www.microchip.com/en-us/products/microcontrollers-and-microprocessors/8-bit-mcus/pic-mcus/pic16f13145)
- [PIC16F13145 Product Page](https://www.microchip.com/en-us/product/PIC16F13145)
- [PIC16F13145 Data Sheet](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/PIC16F13145-Family-Microcontroller-Data-Sheet-DS40002519.pdf)
- [PIC16F13145 Curiosity Nano](https://www.microchip.com/en-us/development-tool/EV06M52A)
- [PIC16F13145 Code Examples on GitHub](https://github.com/orgs/microchip-pic-avr-examples/repositories?q=pic16f13145&type=all)

## Software Used

- [MPLAB® X IDE v6.15 or newer](http://www.microchip.com/mplab/mplab-x-ide)
- [MPLAB® XC8 2.45 or newer](http://www.microchip.com/mplab/compilers)
- [MPLAB® Code Configurator Melody](https://www.microchip.com/en-us/tools-resources/configure/mplab-code-configurator/melody)
- [PIC16F1xxxx_DFP Device Family Pack v1.23.382 or newer](https://packs.download.microchip.com/)

## Hardware Used

The [PIC16F13145 Curiosity Nano](https://www.microchip.com/en-us/development-tool/EV06M52A) Development board is used as a test platform:

<picture>
    <img alt="Shows a picture of the PIC16F13145 Curiosity Nano" src="images/PIC16F13145.png" width="600">
</picture>

## Operation

To program the Curiosity Nano board with this MPLAB X project, follow the steps provided in the [How to Program the Curiosity Nano Board](#how-to-program-the-curiosity-nano-board) chapter.

## Concept

This application showcases the capabilities of using multiple configurations for the CLB module by creating two different versions of a simple clock divider circuit, as illustrated in the diagram below. To keep things simple, the two circuits are identical, with the exception of the clock divider value. The first configuration divides the clock by 2 × 16 = 32, while the second configuration divides the clock by 2 × 128 = 256 and therefore the two digital circuits generate a 1 kHz and 125 Hz, respectively, 50% duty cycle Pulse-Width Modulation (PWM) signal. The two configurations are stored in the Program Flash Memory and are loaded into the CLB registers at runtime. The change between the two configurations is initiated by the press of the onboard button of the Curiosity Nano.

<picture>
    <img alt="Shows a CLB designer diagram of a clock divider" src="images/mcc/circuit.png" width="400">
</picture>

## Setup

- **Clock Control**
  - Clock Source: HFINTOSC
  - HF Internal Clock: 32 MHz
  - Clock Divider: 1

<picture>
    <img alt="Shows an MPLAB® Code Configurator (MCC) Configuration for the System Clock" src="images/mcc/clock.png" width="600">
</picture>

***

- **Configuration Bits**
  - External Oscillator Mode Selection: Oscillator not enabled
  - Power-up Default Value for COSC: HFINTOSC (32 MHz)
  - Brown-out Reset: Disabled
  - Watchdog Timer: Disabled
  - Default values for the rest of the bits

<picture>
    <img alt="Shows an MPLAB® Code Configurator (MCC) Configuration for the Configuration Bits" src="images/mcc/bits.png" width="600">
</picture>

***

- **CLB1**
  - Disabled
  - Clock Selection: MFINTOSC (32 kHz)
  - Clock Divider: 16 (Primary Configuration) / 128 (Alternate Configuration)
  - Configurable Bitstream Address: Disabled
  - Load CLB Bitstream after Reset: Disabled

<picture>
    <img alt="Shows an MPLAB® Code Configurator (MCC) Configuration for the CLB1 module" src="images/mcc/clb1.png" width="600">
</picture>

***

- **GPIO**
  - RA5 (`OUTPUT`) - Digital Output (CLBPPSOUT0)
  - RC3 (`BUTTON`) - Digital Input with Pullup Enabled (GPIO)

<picture>
    <img alt="Shows an MPLAB® Code Configurator (MCC) Configuration for the GPIO module." src="images/mcc/gpio.png" width="600">
</picture>

<picture>
    <img alt="Shows an MPLAB® Code Configurator (MCC) Configuration for the pin grid." src="images/mcc/grid.png" width="600">
</picture>

## Demo

The subsequent illustration presents the output signal from the CLB module, which is a PWM waveform operating at a 50% duty cycle. This diagram emphasizes the shift between the two configurations, specifically from 1 kHz to 125 Hz, a change that is initiated by the simple press of a button.

<picture>
    <img alt="Shows a PWM waveform for the output signal." src="images/output.png" width="1000">
</picture>

## Summary

This application demonstrates the possibility of using multiple configurations on the Configurable Logic Block of the PIC16F13145 device family. The provided code example illustrates a straightforward scenario in which the configurations are alternated in a cyclical manner upon the press of a button.

## How to Program the Curiosity Nano board

This chapter shows how to use the MPLAB X IDE to program a PIC® device with an *ExampleProject.X*. This can be applied for any other projects.

1. Connect the board to the Computer.

2. Open the *ExampleProject.X* project in MPLAB X IDE.

3. Set the **ExampleProject** project as main project.

    Right click on the project in the **Projects** tab and click **Set as Main Project**.

    ![Set as Main Project](images/main-project.png)

4. Clean and build the **ExampleProject** project.

    Right click on the **ExampleProject** project and select **Clean and Build**.

    ![Clean and Build](images/clean-and-build.png)

5. Select the **PIC Curiosity Nano** in the Connected Hardware Tool section of the project settings:

    - Right click on the project and click **Properties**
    - Click on the arrow under the Connected Hardware Tool
    - Select the **PIC Curiosity Nano**, click **Apply** and then click **OK**:

    ![Select the PIC Curiosity Nano](images/device.png)

6. Program the project to the board.

    Right click on the project and click **Make and Program Device**.

    ![Make and Program Device](images/make-and-program.png)

## Contents

- [Back to Related Documentation](#related-documentation)
- [Back to Software Used](#software-used)
- [Back to Hardware Used](#hardware-used)
- [Back to Operation](#operation)
- [Back to Setup](#setup)
- [Back to Summary](#summary)
- [Back to How to Program the Curiosity Nano board](#how-to-program-the-curiosity-nano-board)
- [Back to Top](#getting-started-with-multiple-configurations-for-the-configurable-logic-block-clb---use-case-for-the-pic16f13145-microcontroller-with-mcc-melody)
