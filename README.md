# Interrupt-Driven RGB LED Controller (PIC16F877A)

An embedded systems project implementing a hardware interrupt-driven control system using the **PIC16F877A** microcontroller, developed in the Faculty of Engineering at Damanhour University[cite: 17]. This repository contains code and hardware documentation for two distinct project implementations featuring **Interrupt on Change (IOC)** on PORTB[cite: 17].

---

## 📂 Project Structure

This repository includes two projects:
1. **First Project**: An idle-state system where pressing one of three push buttons wakes the microcontroller to light up specific colors (Red, Green, or Blue) on an RGB LED[cite: 17].
2. **Second Project**: A running background system that continuously cycles an RGB LED through a sequence of 7 colors, utilizing an interrupt button to pause the sequence, show a solid Green color for 2 seconds, and resume[cite: 17].

---

## ⚙️ Hardware Components

* **Microcontroller**: PIC16F877A & PICKit 3.5 Programmer[cite: 17]
* **Lighting**: 1x Common Cathode RGB LED[cite: 17]
* **Input**: 3 Push Buttons (Project 1) / 1 Push Button (Project 2)[cite: 17]
* **Clock Source**: 4 MHz Crystal Oscillator with 2x 15pF capacitors and 1x 100nF capacitor[cite: 17]
* **Resistors**: 1x 10 kΩ, 3x 220 Ω[cite: 17]
* **Peripherals**: Breadboard, jumper wires, and a 5V DC power supply[cite: 17]

---

## 💻 Software Implementation (C Code)

Below is the C code implementation for the **Second Project** (Continuous 7-Color Cycle with Interrupt Override), written for the **mikroC PRO for PIC** IDE[cite: 17]:

```c
/* Declaration */
unsigned short int mask[7] = {
    0b10000000,
    0b01000000,
    0b00100000,
    0b11000000,
    0b01100000,
    0b10100000,
    0b11100000
};
unsigned short int i = 0;
unsigned short int temp = 0; // variable to use as PORTB dump

void interrupt() {
    Delay_ms(100); // debounce
    if (INTCON.RBIF) {
        portd.b7 = 0; portd.b6 = 1; portd.b5 = 0; // turn on green color
        Delay_ms(2000); // wait 2 Sec
        temp = PORTB; // Read PORTB to clear mismatch
        INTCON.RBIF = 0; // Clear Interrupt Flag bit
    }
}

void main() {
    /* Hardware configuration */
    // PortD for LEDS
    portd.b7 = 0;
    portd.b6 = 0;
    portd.b5 = 0; // o/p --> Low
    trisd.b7 = 0;
    trisd.b6 = 0;
    trisd.b5 = 0; // pins --> o/p

    // PortB for interruption
    OPTION_REG.NOT_RBPU = 0; // PortB pull-ups are enabled
    trisb.b4 = 1; // RB4 --> i/p
    temp = portb; // Read PORTB to clear mismatch
    INTCON.RBIF = 0; // RB Port Change Interrupt Flag bit
    INTCON.RBIE = 1; // Enables the RB port change interrupt
    INTCON.GIE = 1; // Enables all interrupts

    while(1) {
        portd = mask[i];
        Delay_ms(500);
        i += 1;
        if (i == 7) i = 0;
    }
}
```[cite: 17]

---

## 🚀 Flashing & ICSP Connections

Burn the compiled `.hex` file to the PIC16F877A using the PICKit Programmer via ICSP[cite: 17]:
* **PICKit Pin 1 (MCLR)** $\rightarrow$ PIC Pin 1[cite: 17]
* **PICKit Pin 2 (VDD)** $\rightarrow$ PIC Pin 11 (+5V)[cite: 17]
* **PICKit Pin 3 (VSS)** $\rightarrow$ PIC Pin 12 (GND)[cite: 17]
* **PICKit Pin 4 (PGD)** $\rightarrow$ PIC Pin 40 (RB7)[cite: 17]
* **PICKit Pin 5 (PGC)** $\rightarrow$ PIC Pin 39 (RB6)[cite: 17]
