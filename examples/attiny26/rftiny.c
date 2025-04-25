
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../rftiny.h"

#define TIMER_CHECK_FOR (unsigned int)0b01111111
#define TIMER_PRESCALER 0b0001
//#define TIMER_CHECK_FOR 156
//#define TIMER_PRESCALER 6

static volatile uint8_t rx_data_len = 0; // How many bits are available at rx_data_buf
static volatile rftiny_buf rx_data_buf = 0; // Data buf

void main() {
	DDRB = _BV(PB1) | _BV(PB2);

	// Configure timer1 for CTC mode
	TIMSK |= _BV(OCIE1A);

	OCR1A = TIMER_CHECK_FOR;
	OCR1C = TIMER_CHECK_FOR;

	TCCR1B = 0
		| _BV(CTC1)
		| ((TIMER_PRESCALER & 0b0001) << CS10)
		| (((TIMER_PRESCALER & 0b0010) >> 1) << CS11)
		| (((TIMER_PRESCALER & 0b0100) >> 2) << CS12)
		| (((TIMER_PRESCALER & 0b1000) >> 3) << CS13);

	// Enable interrupts
	sei();

	rftiny_buf data = rftiny_find_packet();
	cli();

	while(1)
		if(data == 0b00000010)
		 	PORTB = _BV(PB1);
}

ISR(TIMER1_CMPA_vect) {
	uint8_t bit = ((PINB >> PB0) & 1);
	PORTB = bit << PB1 | (!((PORTB >> PB2) & 1)) << PB2;

	rx_data_buf = (rx_data_buf << 1) | bit;
	rx_data_len += 1;
}

uint8_t rftiny_get_bit() {
	while(rx_data_len == 0);
	return (rx_data_buf >> rx_data_len--) & 1;
}

void rftiny_put_buf(rftiny_buf buf) {}