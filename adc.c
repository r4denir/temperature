#include <avr/io.h>

void adc_init() {
        ADMUX = (1<<REFS0);
        ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint16_t adc_read(uint8_t channel) {
   channel = channel & 0b00000111;
   ADMUX |= channel;
   ADCSRA |= (1<<ADSC);

   while(!(ADCSRA & (1<<ADIF)));

   ADCSRA|=(1<<ADIF);

   return(ADC);
}
