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

