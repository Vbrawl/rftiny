#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../rftiny.h"

#define TIMER_CHECK_FOR (unsigned int)145
#define TIMER_PRESCALER 6

// #define TIMER_CHECK_FOR 156
// #define TIMER_PRESCALER 6

static volatile uint8_t tx_data_len = 0; // How many bits are available in tx_data_buf
static volatile rftiny_buf tx_data_buf = 0; // Data buf

void main() {
	DDRB = (1 << PB0);
	PORTB = 0;
	// while(1);

	// Timer 1 configuration
	TCCR1A = 0;
	TCCR1B = 0
		// CTC (Clear Timer on Compare match)
		| (1 << CTC1)
		// Setup prescaler
		| ((TIMER_PRESCALER & 0b0001) << CS10)
		| (((TIMER_PRESCALER & 0b0010) >> 1) << CS11)
		| (((TIMER_PRESCALER & 0b0100) >> 2) << CS12)
		| (((TIMER_PRESCALER & 0b1000) >> 3) << CS13);

	// Timer 1 value for interrupt
	OCR1A = TIMER_CHECK_FOR;

	// Enable Timer 1 interrupt for compare match
	TIMSK |= (1 << OCIE1A);

	// Enable interrupts
	sei();

	rftiny_buf data = 0b00000100;
	rftiny_put_packet(data);

	while(1);
}

ISR(TIMER1_CMPA_vect) {
	if(tx_data_len == 0) return;
	uint8_t bit = (tx_data_buf >> (tx_data_len - 1)) & 1;
	tx_data_len -= 1;

	// PORTB |= (bit << PB0);
	PORTB ^= (1 << PB0);
}

void rftiny_put_buf(rftiny_buf data) {
	while(tx_data_len > 0);
	tx_data_buf = (tx_data_buf << sizeof(data)) | data;
	tx_data_len += sizeof(data);
}

uint8_t rftiny_get_bit() { return 0; }