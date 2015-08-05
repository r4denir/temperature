/* Microcontroller.net */

#ifdef DEBUG
#include <avr/interrupt.h>
#define BAUD 9600UL
#define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)   // clever runden
#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))     // Reale Baudrate
#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD)      // Fehler in Promille, 1000 = kein Fehler.
#if ((BAUD_ERROR<990) || (BAUD_ERROR>1010))
  #error Systematischer Fehler der Baudrate groesser 1% und damit zu hoch! 
#endif

void uart_init() {
    UBRRH = UBRR_VAL >> 8;
    UBRRL = UBRR_VAL & 0xFF;
    UCSRB |= (1<<TXEN);
    UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);       // Asynchron 8N1 
}

uint8_t uart_putc(unsigned char c) {
    while (!(UCSRA & (1<<UDRE)));  /* warten bis Senden moeglich */
    UDR = c;                      /* sende Zeichen */
    return 0;
}
 
void uart_puts (char *s) {
    while (*s) {   /* so lange *s != '\0' also ungleich dem "String-Endezeichen(Terminator)" */
        uart_putc(*s);
        s++;
    }
}
#endif
